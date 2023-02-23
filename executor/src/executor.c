/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/23 11:41:50 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include<stdio.h>

void print_input_cmd_line(char **av);

/*
    We are going to take a cmd and execute its content
    If there are any redirection we take care of them first;

*/

int main(int argc, char **argv, char **env)
{
    t_simple_cmds   cmd;
    char            **arr = NULL;
    (void)          argc;
    (void)          argv;
    arr = ft_malloc(sizeof (char *) * 3);
    arr[0] = ft_malloc(sizeof(char) * 10);
    arr[1] = ft_malloc(sizeof(char) * 10);
    arr[0] = "echo";
    arr[1] = "a";
    arr[2] = NULL;
    cmd.av = arr;
    cmd.next = NULL;
    cmd.redirections = NULL;
    executor(&cmd, env);
    return (0);
}

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

	printf("%d, %d\n", fd[0], fd[1]);
	if (pipe(fd) == -1)
		return ;
	print_input_cmd_line(cmd->av);
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
