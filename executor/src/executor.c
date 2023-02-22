/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/22 13:02:12 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"executor.h"
#include<stdio.h>


void executor(t_simple_cmds *cmd);
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
    arr = ft_malloc(sizeof (char *) * 2);
    arr[0] = ft_malloc(sizeof(char) * 10);
    arr[1] = ft_malloc(sizeof(char) * 10);
    arr[0] = "echo";
    arr[1] = "a";
    cmd.av = arr;
    cmd.num_redirections = 0;
    cmd.next = NULL;
    executor(&cmd);
    return (0);
}

void executor(t_simple_cmds *cmd)
{
	char	**path_arr;
	char	*cmd_path;
	char	*cmd_access;
	int i;
	int return_access;

	path_arr = ft_split(getenv("PATH"), ':');
    printf("%s\n", cmd->av[0]);
    printf("%s\n", cmd->av[1]);
	
	i = 0;
	//modifier le path pour qu'il puisse trouver l'exec de n'importe ou;
	//=>retourner chercher apd de la root avec //;
	while (path_arr[i] != NULL)
	{
		cmd_path = ft_strjoin("/", cmd->av[0]);
		cmd_access = ft_strjoin(path_arr[i], cmd_path);
    	printf("%s\n", path_arr[i]);
    	printf("%s\n", cmd_access);
		return_access = access(cmd_access, X_OK);
		printf("access = %d\n", return_access);
		if (return_access == 0)
			execve(cmd_access, cmd->av + 1, NULL);
		i++;
	}	

}
