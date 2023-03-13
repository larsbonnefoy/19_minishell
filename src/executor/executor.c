/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/13 13:36:24 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"
#include "../../Includes/minishell.h"

int		handle_redir(t_simple_cmds *cmd, int *fd_pipe, int fd_in);
int		process(int *fd_pipe, int fd_in, t_simple_cmds *cmd, char ***env, t_env **l_env);

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
	int				fd_pipe[2];
	int				fd_in;
	t_simple_cmds	*curr;
	int				std_in;
	int				std_out;
	int				self_built_nb;

	if (!cmd)
		return ;
	fd_in = STDIN_FILENO;
	fd_pipe[0] = -1;
	fd_pipe[1] = -2;
	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	curr = cmd;
	curr->pid = -2; //could be set when init cmd
	if (is_local(curr->av[0]))
		curr->av = make_local(curr->av);
	print_cmd(curr);
	self_built_nb = is_self_builtin(curr->av[0], curr->pid);
	if (curr->next == NULL && self_built_nb != -1)
	{
		handle_redir(curr, fd_pipe, fd_in);
		exec_s_built(cmd->av, env, l_env, self_built_nb);
	}
	else
	{
		while (curr) //if cmd->next we have to pipe
		{
			if (curr->next != NULL)
			{
				if (pipe(fd_pipe) == -1)
					return ;
			}
			fd_in = process(fd_pipe, fd_in, curr, env, l_env);
			curr = curr->next;
		}
		curr = cmd;
		while (curr)
		{
			waitpid(curr->pid, NULL, 0);
			curr = curr->next;
		}
	}
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_out);
	close(std_in);
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
int	process(int *fd_pipe, int fd_in, t_simple_cmds *cmd, char ***env, t_env **l_env)
{
	int	fd_out;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (handle_redir(cmd, fd_pipe, fd_in) != 0)
			exit(EXIT_FAILURE);
		ft_execve(cmd, env, l_env);
		exit(EXIT_SUCCESS);
	}
	if (cmd->n > 0)
		close(fd_in);
	close(fd_pipe[1]);
	return (fd_pipe[0]);
//si on a une redirection sur fd_out le fd_in du prochain pipe sera sur STD_IN
}

int	handle_redir(t_simple_cmds *cmd, int *fd_pipe, int fd_in)
{
	if (cmd->next != NULL || has_outfile(cmd->redirections))
	{
		fd_pipe[1] = get_out_fd(cmd, fd_pipe[1]);
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
			return (-1);
		if (cmd->next != NULL)
			close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	if (cmd->n > 0 || is_infile(cmd->redirections)) //OR IN REDIR
	{
		fd_in = get_in_fd(cmd, fd_in);
		if (fd_in == -1)
			return (fd_in);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(fd_in);
	}
	return (0);
}
