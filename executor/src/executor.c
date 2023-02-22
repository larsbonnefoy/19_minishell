/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/22 16:38:02 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include<stdio.h>

void print_input_cmd_line(char **av);
char *get_access_path(char **av, char *path);

/*
    We are going to take a cmd and execute its content
    If there are any redirection we take care of them first;

*/

int main(int argc, char **argv)
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
    cmd.num_redirections = 0;
    cmd.next = NULL;
    executor(&cmd);
    return (0);
}

/*
 *	We take each node of the cmd table
 * 	1. handle redirection
 * 	2. execute command
 * 	3. return right fd so that the parent process can read from it in case of multiple pipes
 * 	/!\ free correctly all the elements as execve replaces the process 
 */
void executor(t_simple_cmds *cmd)
{
	char	**path_arr;
	char	*access_path;
	int i;
	int return_access;

	path_arr = ft_split(getenv("PATH"), ':');
	print_input_cmd_line(cmd->av);
	i = 0;
	while (path_arr[i] != NULL)
	{
		access_path = get_access_path(cmd->av, path_arr[i]);
		return_access = access(access_path, X_OK);
		if (return_access == 0)
			execve(access_path, cmd->av, NULL);
		else
			free(access_path);
		i++;
	}	
}

char *get_access_path(char **av, char *path)
{
	char	*access_path;
	char	*mod_cmd;	

	mod_cmd = ft_strjoin("/", av[0]);
	access_path = ft_strjoin_ff(path, mod_cmd);
	return (access_path);
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
