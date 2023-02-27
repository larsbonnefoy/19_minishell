/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/27 16:14:10 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../src/minishell.h"

int 	process(int *fd_pipe, int fd_in, t_simple_cmds *cmd, char **env);
void 	print_input_cmd_line(char **av);
int		get_redir(t_simple_cmds *cmd);
/*
 *	We take each node of the cmd table
 * 	1. handle redirection
 * 	2. execute command
 * 	3. return right fd so that the parent process can read from it in case of multiple pipes
 * 	fd[0] == READ == IN
 * 	fd[1] == WRITE == OUT
 * 	/!\ free correctly all the elements as execve replaces the process 
 */
void executor(t_simple_cmds *cmd, char **env)
{
	int		fd_pipe[2];
	int		pid;
	int		fd_in;
	t_simple_cmds *curr;
	int		std_in;

	if (!cmd->redirections)
		fd_in = STDIN_FILENO; //par defaut fd_in est mis a STDIN, par apres il est set a fd[0] (read) du pipe
	else
	{
		printf("redir lexer\n");
		lexer_print_list(&cmd->redirections);
		fd_in = get_redir(cmd);
	}
	fd_pipe[0] = 0; //init fd_pipe dans le cas ou curr->next == NULL;
	fd_pipe[1] = 1;
	std_in = dup(STDIN_FILENO); //stdin = 3 pointe sur l'entree std
	curr = cmd;
	while (curr) //if cmd->next we have to pipe
	{ 
		if (curr->next != NULL)
		{
			if (pipe(fd_pipe) == -1)
				return ;
		}
		fd_in = process(fd_pipe, fd_in, curr, env); //read access of pipe will be stdin of the next pipe
		curr = curr->next;
	}
	curr = cmd;
	while (curr)
	{
		waitpid(curr->pid, NULL, 0);
		curr=curr->next;
	}
	int in = dup2(std_in, STDIN_FILENO);
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
		printf("cmd n%d\n", cmd->n);
		printf("fd_pipe[0] = %d, fd_pipe[1] = %d, fd_in = %d\n", fd_pipe[0], fd_pipe[1], fd_in);
		if (cmd->next != NULL) //redir output to pipe because we are not at there is at least a pipe left
		{
			if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
				return (-2);
			close(fd_pipe[1]);
			close(fd_pipe[0]);
		}
		if (cmd->n > 0)
		{
			if (dup2(fd_in, STDIN_FILENO) == -1)
				return (-2);
			close(fd_in);
		}
		ft_execve(cmd->av, env);
	}
	if (cmd->n > 0)
		close(fd_in);
	if (cmd->next != NULL)
		close(fd_pipe[1]);
	return (fd_pipe[0]);
}

int get_redir(t_simple_cmds *cmd)
{



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
