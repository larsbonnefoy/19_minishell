/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/03 17:12:32 by lbonnefo         ###   ########.fr       */
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
char	*get_out_file(t_simple_cmds *cmd);
int		get_out_token(t_simple_cmds *cmd, char *file);
int		get_out_fd(t_simple_cmds *cmd, int pipe_write);
int		get_in_fd(t_simple_cmds *cmd,int fd_in);

int 	debug_stdout;
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

	debug_stdout = dup(STDOUT_FILENO);

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
	close(debug_stdout);
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
		ft_execve(cmd->av, env, debug_stdout);
	}
	if (cmd->n > 0)
		close(fd_in);
	close(fd_pipe[1]);
	return (fd_pipe[0]); //si on a une redirection sur fd_out le fd_in du prochain pipe sera sur STD_IN
}

int get_out_fd(t_simple_cmds *cmd, int pipe_write)
{
	char	*file;
	int		token;
	int		fd;

	if (is_outfile(cmd->redirections))
	{
		file = get_out_file(cmd);	
		token = get_out_token(cmd, file);
		if (token == D_GREATER)
			fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{	
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (cmd->next != NULL)
			close(pipe_write);
		printf("opened %s on %d\n", file, fd);
		return (fd);
	}
	else
		return (pipe_write);
}

/*
 * opens fd of infile redirection if there is one, else returns fd_in
*/
int get_in_fd(t_simple_cmds *cmd,int fd_in)
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

char *get_out_file(t_simple_cmds *cmd)
{
	t_lexer *redir;
	char	*file;

	redir = cmd->redirections;
	file = NULL;
	while (redir)
	{
		if (redir->token == GREATER || redir->token == D_GREATER)
			file = redir->str;
		redir = redir->next;
	}
	return (file);
}

int get_out_token(t_simple_cmds *cmd, char *file)
{
	int token;
	t_lexer	*redir;

	redir = cmd->redirections;
	while(redir)
	{
		if (file == redir->str)
			token = redir->token;
		redir = redir->next;
	}
	return (token);
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
