/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/14 15:58:00 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"
#include "../../Includes/minishell.h"

typedef	struct	s_filedes
{
	int fd_pipe[2];
	int	fd_in;
	int std_in;
	int	std_out;

} t_fildes;

typedef struct s_envs
{
	char ***env;
	t_env **l_env;
} t_envs;

static	int		handle_redir(t_simple_cmds *cmd, t_fildes *fildes, t_env **l_env);
static int		process(t_simple_cmds *cmd, t_fildes *fildes ,t_envs *envs);
static	int		create_struct(t_fildes *fildes, t_envs *envs, char ***env, t_env **l_env);
static	int		restore_fidles(t_fildes *fildes);

/*
 *	We take each node of the cmd table
 * 	1. handle redirection
 * 	2. execute command
 * 	3. return right fd so that the parent process can read from 
 * 	it in case of multiple pipes
 * 	fd[0] == READ == IN
 * 	fd[1] == WRITE == OUT
 * 	fork with execve (=> standard non builtin functions)
 */
void	executor(t_simple_cmds *cmd, char ***env, t_env **l_env)
{
	t_simple_cmds	*curr;
	int				self_built_nb;
	t_fildes		fildes;
	t_envs			envs;

	if (!cmd)
		return ;
	create_struct(&fildes, &envs, env, l_env);
	curr = cmd;
	if (is_local(curr->av[0]))
		curr->av = make_local(curr->av);
	print_cmd(curr);
	self_built_nb = is_self_builtin(curr->av[0], curr->pid);
	if (curr->next == NULL && self_built_nb != -1)
	{
		if (handle_redir(curr, &fildes, l_env) != 0)
		{
			restore_fidles(&fildes);
			return ;
		}
		exec_s_built(cmd->av, env, l_env, self_built_nb);
	}
	else
	{
		while (curr) //if cmd->next we have to pipe
		{
			if (curr->next != NULL)
			{
				if (pipe(fildes.fd_pipe) == -1)
					return ;
			}
			fildes.fd_in = process(curr, &fildes, &envs);
			curr = curr->next;
		}
		curr = cmd;
		while (curr)
		{
			waitpid(curr->pid, NULL, 0);
			curr = curr->next;
		}
	}
	restore_fidles(&fildes);
}

/*
 * Handle child process by redirection the inputs and outputs
 * Le process doit lire fd[0] sur
 * 	-> l'entrée standard quand c'est la permière fois
 * 	-> la sortie de pipe précédent les fois d'aprés
 * Le process doit ecrire fd[1] sur
 * 	-> la sortie standard quand c'est la dernière commande
 * 	-> sur la sortie du pipe ACTUEL
 * dup2(fildes, fildes2)
 * 	fildes2 points sur fildes 
 * 		=> on peut ecrire sur le document depuis fildes ou fildes2
 * 		c'est pour ça qu'on close a chaque fois pcq avec dup on a 
 * 		ouvert sur une nouvelle entree
 */
static int	process(t_simple_cmds *cmd, t_fildes *fildes , t_envs *envs)
{
	int	fd_out;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (handle_redir(cmd, fildes, envs->l_env) != 0)
			exit(EXIT_FAILURE);
		ft_execve(cmd, envs->env, envs->l_env);
		exit(EXIT_SUCCESS);
	}
	if (cmd->n > 0)
		close(fildes->fd_in);
	close(fildes->fd_pipe[1]);
	return (fildes->fd_pipe[0]);
}

static	int		handle_redir(t_simple_cmds *cmd, t_fildes *fildes, t_env **l_env)
{	
	if (cmd->n > 0 || has_infile(cmd->redirections))
	{
		fildes->fd_in = get_in_fd(cmd, fildes->fd_in, l_env, fildes->std_in);
		if (fildes->fd_in == -1)
			return (-1);
		if (dup2(fildes->fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(fildes->fd_in);
	}
	if (cmd->next != NULL || has_outfile(cmd->redirections))
	{
		fildes->fd_pipe[1] = get_out_fd(cmd, fildes->fd_pipe[1]);
		if (fildes->fd_pipe[1] == -1)
			return (-1);
		if (dup2(fildes->fd_pipe[1], STDOUT_FILENO) == -1)
			return (-1);
		if (cmd->next != NULL)
			close(fildes->fd_pipe[0]);
		close(fildes->fd_pipe[1]);
	}

	return (0);
}

static	int	create_struct(t_fildes *fildes, t_envs *envs, char ***env, t_env **l_env)
{

	fildes->fd_in = STDIN_FILENO;
	fildes->fd_pipe[0] = -1;
	fildes->fd_pipe[1] = -2;
	fildes->std_in = dup(STDIN_FILENO);
	fildes->std_out = dup(STDOUT_FILENO);
	envs->env = env;
	envs->l_env = l_env;
	return (0);
}

static int restore_fidles(t_fildes *fildes)
{
	if (dup2(fildes->std_in, STDIN_FILENO) == -1)
		return (-1);
	if (dup2(fildes->std_out, STDOUT_FILENO) == -1)
		return (-1);
	close(fildes->std_out);
	close(fildes->std_in);
	return (0);
}
