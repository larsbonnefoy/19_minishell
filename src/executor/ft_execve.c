/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:27:03 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/07 14:36:43 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"
char	*get_access_path(char **av, char *path);
int		is_self_builtin(char *func_name);
int		exec_s_built(char **av, char ***env, t_env **l_env, int self_built_nb);

/*
 * Check if function is a self coded func or not and execute it
 * TO DO: check in working dir
*/
void ft_execve(char **av, char ***env, t_env **l_env)
{
	char	*path_str; 
	char	**path_arr;
	char	*access_path;
	int		i;
	int		return_access;
	int		self_builtin_nb;

	self_builtin_nb = is_self_builtin(av[0]);
	if (self_builtin_nb != -1)
		exec_s_built(av, env, l_env, self_builtin_nb);	
	else
	{
		path_str = ft_strjoin(getenv("PATH"), ":");
		path_str = ft_strjoinf(path_str, getenv("PWD"));
		path_arr = ft_split(path_str, ':');
		i = 0;
		while (path_arr[i] != NULL)
		{
			access_path = get_access_path(av, path_arr[i]);
			return_access = access(access_path, X_OK);
			if (return_access == 0)
			{
				if (execve(access_path, av, *env) == -1)
				{
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else
				free(access_path);
			i++;
		}
		free(path_arr);
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(EXIT_FAILURE);
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

int	exec_s_built(char **av, char ***env, t_env **l_env, int self_builtin_nb)
{
	int	(*func[7])(char **av, char ***env, t_env **l_env);
	int	res;

	printf("exec builtin\n");
	func[0] = &ft_echo;
	func[1] = &ft_pwd;
	func[2] = &ft_exit;
	func[3] = &ft_env;
	func[4] = &ft_cd;
	func[5] = &ft_export;
	func[6] = &ft_unset;

	res = func[self_builtin_nb](av, env, l_env);

	return (res);
}

int	is_self_builtin(char *func_name)
{
	if (ft_strncmp(func_name, "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(func_name, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(func_name, "exit", 5) == 0)
		return (2);
	else if (ft_strncmp(func_name, "env", 4) == 0)
		return (3);
	else if (ft_strncmp(func_name, "cd", 3) == 0)
		return (4);
	else if (ft_strncmp(func_name, "export", 7) == 0)
		return (5);
	else if (ft_strncmp(func_name, "unset", 6) == 0)
		return (6);
	return (-1);
}
