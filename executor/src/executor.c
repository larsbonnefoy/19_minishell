/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/23 17:03:10 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../src/minishell.h"

void 	yeet_child(int *fd, int fd_in, t_simple_cmds *cmd, char **env);
void 	print_input_cmd_line(char **av);

/*
 *	We take each node of the cmd table
 * 	1. handle redirection
 * 	2. execute command
 * 	3. return right fd so that the parent process can read from it in case of multiple pipes
 * 	/!\ free correctly all the elements as execve replaces the process 
 */
void executor(t_simple_cmds *cmd, char **env)
{
	int		fd[2];
	int		pid;
	int		in_fd;

	print_input_cmd_line(cmd->av);
	in_fd = STDIN_FILENO;
	while (cmd->next) //if cmd->next we have to pipe
	{ 
		if (pipe(fd) == -1)
			return ;
		printf("Parent process fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
		pid = fork();
		if (pid == 0)
			yeet_child(fd, in_fd, cmd, env);
		in_fd = fd[0]; //read access of pipe will be stdin of the next pipe
		close(fd[1]);
		cmd = cmd->next;
		printf("------------------------\n");
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
void 	yeet_child(int *fd, int fd_in, t_simple_cmds *cmd, char **env)
{
	printf("	child executing %s\n", cmd->av[0]);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	ft_execve(cmd->av, env);
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
