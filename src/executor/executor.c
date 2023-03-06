/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/06 11:23:12 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"

int 	process(int *fd_pipe, int fd_in, t_simple_cmds *cmd, char **env);
/*
 *	We take each node of the cmd table
 * 	1. handle redirection
 * 	2. execute command
 * 	3. return right fd so that the parent process can read from it in case of multiple pipes
 * 	fd[0] == READ == IN
 * 	fd[1] == WRITE == OUT
 * 	fork with execve (=> standard non builtin functions)
 */
void executor(t_simple_cmds *cmd, char **env)
{
	int		fd_pipe[2];
	int		pid;
	int		fd_in;
	t_simple_cmds *curr;
	int		std_in;
	int		std_out;

	fd_in = STDIN_FILENO;
	fd_pipe[0] = -1;
	fd_pipe[1] = -2;
	std_in = dup(STDIN_FILENO); //stdin = 3 pointe sur le fichier "entre standard (/prompt)"
	std_out = dup(STDOUT_FILENO);
	curr = cmd;
	while (curr) //if cmd->next we have to pipe
	{ 
		if (curr->redirections)
			lexer_print_list(&curr->redirections);
		if (curr->next != NULL)
		{
			if (pipe(fd_pipe) == -1)
				return ;
		}
		fd_in = process(fd_pipe, fd_in, curr, env ); //read access of pipe will be stdin of the next pipe
		curr = curr->next;
	}
	curr = cmd;
	while (curr)
	{
		waitpid(curr->pid, NULL, 0);
		curr=curr->next;
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
 * 		c'est pour ça qu'on close a chaque fois pcq avec dup on a ouvert sur une nouvelle entree
 */
int 	process(int *fd_pipe, int fd_in, t_simple_cmds *cmd, char **env)
{
	int fd_out;

	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (cmd->next != NULL || is_outfile(cmd->redirections)) //redir output to pipe because we are not at there is at least a pipe left || redir the output to the file
		{
			fd_pipe[1] = get_out_fd(cmd, fd_pipe[1]);
			dup2(fd_pipe[1], STDOUT_FILENO);
			if (cmd->next != NULL)
				close(fd_pipe[0]);
			close(fd_pipe[1]);
		}
		if (cmd->n > 0 || is_infile(cmd->redirections)) //OR IN REDIR
		{
			fd_in = get_in_fd(cmd, fd_in);
			if (dup2(fd_in, STDIN_FILENO) == -1)
				return (-2);
			close(fd_in);
		}
		ft_execve(cmd->av, env);
	}
	if (cmd->n > 0)
		close(fd_in);
	close(fd_pipe[1]);
	return (fd_pipe[0]); //si on a une redirection sur fd_out le fd_in du prochain pipe sera sur STD_IN
}
