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

void print_input_cmd_line(char **av);
void	exec_last_cmd(t_simple_cmds *cmd, char **env, int fd[2], int nbr_pipe);

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
	int		old_fd;
	int		nbr_pipe;

	if (pipe(fd) == -1)
		return ;
	print_input_cmd_line(cmd->av);
	nbr_pipe = 0;
	while (cmd->next) //if cmd->next we have to pipe
	{
		printf("Parent process fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
		pid = fork();
		if (pid == 0)
		{
			printf("	child executing %s\n", cmd->av[0]);
			if (nbr_pipe != 0)
				dup2(fd[0], STDIN_FILENO); 
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			ft_execve(cmd->av, env);
		}
		old_fd = fd[0];
		close(fd[1]);
		cmd = cmd->next;
		nbr_pipe++;
		printf("------------------------\n");
	}
	exec_last_cmd(cmd, env, fd, nbr_pipe);
}

void	exec_last_cmd(t_simple_cmds *cmd, char **env, int fd[2], int nbr_pipe)
{
	int pid2;

	printf("Parent process fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
	pid2 = fork();
	if (pid2 == 0)
	{
		if (nbr_pipe != 0)
			dup2(fd[0], STDIN_FILENO);
		printf("	child process fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
		printf("	last child executing %s\n", cmd->av[0]);
		close(fd[0]);
		close(fd[1]);
		ft_execve(cmd->av, env);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, NULL, 0);
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
