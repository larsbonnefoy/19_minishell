/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/01 15:21:55 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../src/minishell.h"
#include <fcntl.h>
#include <unistd.h>

int 	is_infile(t_lexer *redirection);
int		get_out_redir(t_simple_cmds *cmd, int pipe_write);
int 	process(int *fd_pipe, int fd_in, t_simple_cmds *cmd, char **env);
int 	get_in_redir(t_simple_cmds *cmd, int fd_in);
void 	print_input_cmd_line(char **av);
int		is_outfile(t_lexer *redirections);

/*
 *	We take each node of the cmd table
 * 	1. handle redirection
 * 	2. execute command
 * 	3. return right fd so that the parent process can read from it in case of multiple pipes
 * 	fd[0] == READ == IN
 * 	fd[1] == WRITE == OUT
 * 	/!\ free correctly all the elements as execve replaces the process 
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
	fd_pipe[0] = 0; //init fd_pipe dans le cas ou curr->next == NULL;
	fd_pipe[1] = 1;
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
		fd_in = get_in_redir(curr, fd_in);
		fd_in = process(fd_pipe, fd_in, curr, env); //read access of pipe will be stdin of the next pipe
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
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		//printf("cmd n%d\n", cmd->n);
		//printf("fd_pipe[0] = %d, fd_pipe[1] = %d, fd_in = %d\n", fd_pipe[0], fd_pipe[1], fd_in);
		fd_pipe[1] = get_out_redir(cmd, fd_pipe[1]);
		if (cmd->next != NULL || is_outfile(cmd->redirections)) //redir output to pipe because we are not at there is at least a pipe left || redir the output to the file
		{
			if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
				return (-2);
			close(fd_pipe[1]);
			close(fd_pipe[0]);
		}
		if (is_infile(cmd->redirections) || cmd->n > 0) //OR IN REDIR
		{
			if (dup2(fd_in, STDIN_FILENO) == -1)
				return (-2);
			close(fd_in);
		}
		ft_execve(cmd->av, env);
	}
	if (is_infile(cmd->redirections) || cmd->n > 0) //OR IN REDIR
		close(fd_in);
	if (cmd->next != NULL || is_outfile(cmd->redirections))
		close(fd_pipe[1]);
	return (fd_pipe[0]); //si on a une redirection sur fd_out le fd_in du prochain pipe sera sur STD_IN
}

/*
 * opens fd of infile redirection if there is one, else returns fd_in
 *
*/
int get_in_redir(t_simple_cmds *cmd,int fd_in)
{
	t_lexer *redir; 	
	int 	fd;
	char 	*file;
	
	redir = cmd->redirections;
	file = NULL;
	while (redir)
	{
		if (redir->token == LOWER)
			file = redir->str;
		redir=redir->next;
	}
	if (file)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			perror("open");
		close(fd_in);
		return (fd);
	}
	return (fd_in);
}

int get_out_redir(t_simple_cmds *cmd, int pipe_write)
{
	t_lexer *redir;
	int fd;
	char *file;
	int  token;

	redir = cmd->redirections;
	file = NULL;
	while (redir)
	{
		if (redir->token == GREATER || redir->token == D_GREATER)
		{
			file = redir->str;
			token = redir->token;
		}	
		redir = redir->next;
	}
	if (file)
	{ 
		if (token == D_GREATER)
			fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		close(pipe_write);
		return (fd);
	}
	return (pipe_write);
}

int is_infile(t_lexer *redirection)
{
	t_lexer *curr_redir;
	curr_redir = redirection;
	while (curr_redir)
	{
		if (curr_redir->token == LOWER)
			return (1);
		curr_redir=curr_redir->next;
	}
	return (0);
}

int is_outfile(t_lexer *redirections)
{
	t_lexer *curr_redir;
	curr_redir = redirections;
	while (curr_redir)
	{
		if (curr_redir->token == D_GREATER || curr_redir->token == GREATER)
			return (1);
		curr_redir=curr_redir->next;

	}
	return (0);
}

void print_input_cmd_line(char **av)
{
	int i;

	i = 0;
	while (av[i] != NULL)
	{
		printf("[%s] ", av[i]);
		i++;
	}
	printf("\n");
}
