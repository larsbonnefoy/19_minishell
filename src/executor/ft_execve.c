/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:27:03 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/06 11:23:25 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"
/*
 * Check if function is a self coded func or not and execute it
 * TO DO: check in working dir
*/
void ft_execve(char **av, char **env)
{
	char	**path_arr;
	char	*access_path;
	int		i;
	int		return_access;

	//if (is_self_builtin(av[0]))	
		//exec our function
	//else
	path_arr = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path_arr[i] != NULL)
	{
		access_path = get_access_path(av, path_arr[i]);
		return_access = access(access_path, X_OK);
		if (return_access == 0)
		{
			if (execve(access_path, av, env) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
			free(access_path);
		i++;
	}
	perror("access");
	exit(EXIT_FAILURE);
}

char *get_access_path(char **av, char *path)
{
	char	*access_path;
	char	*mod_cmd;	

	mod_cmd = ft_strjoin("/", av[0]);
	access_path = ft_strjoin_ff(path, mod_cmd);
	return (access_path);
}
