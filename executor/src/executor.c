/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/25 15:03:40 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../src/minishell.h"

int 	process(int *fd_pipe, int fd_in, t_simple_cmds *cmd, char **env, int n);
void 	print_input_cmd_line(char **av);

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
	int		in_fd;
	int		n;
	t_simple_cmds *tmp_cmd;

	print_input_cmd_line(cmd->av);
	in_fd = STDIN_FILENO;
	n = 0;
	tmp_cmd = cmd;
	while (cmd) //if cmd->next we have to pipe
	{ 
		if (cmd->next != NULL)
			if (pipe(fd_pipe) == -1)
				return ;
		printf("Parent process fd[0] = %d, fd[1] = %d, in_fd = %d\n", fd_pipe[0], fd_pipe[1], in_fd);
		in_fd = process(fd_pipe, in_fd, cmd, env, n); //read access of pipe will be stdin of the next pipe
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		cmd = cmd->next;
		n++;
		printf("------------------------\n");
	}
	tmp_cmd = cmd;
	while (tmp_cmd)
	{
	
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
 * 		c'est pour ça qu'on close a chaque fois pcq avec dup on a ouvert sur une nouvelle entree
 */
int 	process(int *fd, int fd_in, t_simple_cmds *cmd, char **env, int n)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		printf(" ->child executing %s\n", cmd->av[0]);
		printf(" ->read from fd_in  = %d\n", fd_in);
		if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
			return (-2);
		close(fd[fd_in]);
		close(fd[1]);
		close(fd[0]);
		ft_execve(cmd->av, env);
	}
	return (fd[0]);
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
