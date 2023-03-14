/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/14 13:18:40 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"
#include "../../Includes/minishell.h"

static	int		handle_redir(t_simple_cmds *cmd, int *fd_pipe, int fd_in, t_env **l_env, int std_in);
static 	int		process(int *fd_pipe, int fd_in, t_simple_cmds *cmd, char ***env, t_env **l_env, int std_in);

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

int	set_structs(t_envs *envs, t_fildes *fildes, char ***env, t_env **l_env);
int	restore_fildes(t_fildes *fildes);

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
	t_fildes		*fildes;
	t_envs			*envs;
	
	int fd_pipe[2];
	int fd_in = STDIN_FILENO;
	fd_pipe[0] = -1;
	fd_pipe[1] = -2;
	int std_in = dup(STDIN_FILENO);
	int std_out = dup(STDOUT_FILENO);
	if (!cmd)
		return ;
	//if (set_structs(envs, fildes, env, l_env) != 0)
	//	return ;
	curr = cmd;
	if (is_local(curr->av[0]))
		curr->av = make_local(curr->av);
	print_cmd(curr);
	self_built_nb = is_self_builtin(curr->av[0], curr->pid);
	if (curr->next == NULL && self_built_nb != -1)
	{
		if (handle_redir(curr, fd_pipe, fd_in, l_env, std_in) != 0)
		{
			restore_fildes(fildes);
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
				if (pipe(fildes->fd_pipe) == -1)
					return ;
			}
			fildes->fd_in = process(fd_pipe, fd_in, curr, env, l_env, std_in);
			curr = curr->next;
		}
		curr = cmd;
		while (curr)
		{
			waitpid(curr->pid, NULL, 0);
			curr = curr->next;
		}
	}
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
int	process(int *fd_pipe, int fd_in, t_simple_cmds *cmd, char ***env, t_env **l_env, int std_in)
{
	int	fd_out;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (handle_redir(cmd, fd_pipe, fd_in, l_env, std_in) != 0)
			exit(EXIT_FAILURE);
		ft_execve(cmd, env, l_env);
		exit(EXIT_SUCCESS);
	}
	if (cmd->n > 0)
		close(fd_in);
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}

int	handle_redir(t_simple_cmds *cmd, int *fd_pipe, int fd_in, t_env **l_env, int std_in)
{
	if (cmd->next != NULL || has_outfile(cmd->redirections))
	{
		fd_pipe[1] = get_out_fd(cmd, fd_pipe[1]);
		if (fd_pipe[1] == -1)
			return (-1);
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
			return (-1);
		if (cmd->next != NULL)
			close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	if (cmd->n > 0 || has_infile(cmd->redirections))
	{
		fd_in = get_in_fd(cmd, fd_in, l_env, std_in);
		if (fd_in == -1)
			return (-1);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(fd_in);
	}
	return (0);
}

int	set_structs(t_envs *envs, t_fildes *fildes, char ***env, t_env **l_env)
{
	fildes->fd_in = STDIN_FILENO;
	fildes->fd_pipe[0] = -1;
	fildes->fd_pipe[1] = -2;
	fildes->std_in = dup(STDIN_FILENO);
	fildes->std_out = dup(STDOUT_FILENO);
	if (fildes->std_in == -1 || fildes->std_out == -1)
		return (-1);
	envs->env = env;
	envs->l_env = l_env;
	return (0);
}

int	restore_fildes(t_fildes *fildes)
{
	if (dup2(fildes->std_in, STDIN_FILENO) == -1)
	{
		ft_perror("dup2", NULL);
		return (-1);
	}
	if (dup2(fildes->std_out, STDOUT_FILENO == -1))
	{
		ft_perror("dup2", NULL);
		return (-1);
	}
	close(fildes->std_out);
	close(fildes->std_in);
	return (0);
}
