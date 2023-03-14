/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:27:03 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/14 18:06:04 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"
#include "../../Includes/minishell.h"

char	*get_access_path(char **av, char *path);
int		is_self_builtin(char *func_name, int cmd_pid);
int		access_exec(char *access_path, t_simple_cmds *cmd, char ***env);
int		exec_s_built(char **av, char ***env, t_env **l_env, int self_built_nb);
int		ft_void(char **av, char ***env, t_env **l_env);
int		is_in_child(int ret_value, int cmd_pid);

/*
 * Check if function is a self coded func or not and execute it
*/
void	ft_execve(t_simple_cmds *cmd, char ***env, t_env **l_env)
{
	char	**path_arr;
	char	*access_path;
	int		i;
	int		self_builtin_nb;

	self_builtin_nb = is_self_builtin(cmd->av[0], cmd->pid);
	if (self_builtin_nb != -1)
		global = exec_s_built(cmd->av, env, l_env, self_builtin_nb);
	else
	{
		if (ft_strchr(cmd->av[0], '/') != NULL)
			access_exec(cmd->av[0], cmd, env);
		else
		{
			//fix no PATH
			path_arr = ft_split(ft_getenv("PATH", l_env), ':');
			i = 0;
			while (path_arr[i] != NULL)
			{
				access_path = get_access_path(cmd->av, path_arr[i]);
				if (access_exec(access_path, cmd, env) == -1)
					free(access_path);
				i++;
			}
		}
		free(path_arr);
		ft_perror(cmd->av[0], ": command not found");
		exit(127); //set exit_code to 127
	}
}

int	access_exec(char *access_path, t_simple_cmds *cmd, char ***env)
{
	int	return_access;

	return_access = access(access_path, X_OK);
	if (return_access == 0)
	{
		if (execve(access_path, cmd->av, *env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	return (return_access);
}

char	*get_access_path(char **av, char *path)
{
	char	*access_path;
	char	*mod_cmd;	

	mod_cmd = ft_strjoin("/", av[0]);
	access_path = ft_strjoin_ff(path, mod_cmd);
	return (access_path);
}

int	exec_s_built(char **av, char ***env, t_env **l_env, int self_builtin_nb)
{
	int	(*func[9])(char **av, char ***env, t_env **l_env);
	int	res;

	func[0] = &ft_echo;
	func[1] = &ft_pwd;
	func[2] = &ft_exit;
	func[3] = &ft_env;
	func[4] = &ft_cd;
	func[5] = &ft_export;
	func[6] = &ft_unset;
	func[7] = &ft_local;
	func[8] = &ft_void;
	res = func[self_builtin_nb](av, env, l_env);
	return (res);
}

int	is_self_builtin(char *func_name, int cmd_pid)
{
	if (ft_strncmp(func_name, "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(func_name, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(func_name, "exit", 5) == 0)
		return (is_in_child(2, cmd_pid));
	else if (ft_strncmp(func_name, "env", 4) == 0)
		return (3);
	else if (ft_strncmp(func_name, "cd", 3) == 0)
		return (4);
	else if (ft_strncmp(func_name, "export", 7) == 0)
		return (5);
	else if (ft_strncmp(func_name, "unset", 6) == 0)
		return (6);
	else if (ft_strncmp(func_name, "ft_local", 9) == 0)
		return (is_in_child(7, cmd_pid));
	return (-1);
}

int	ft_void(char **av, char ***env, t_env **l_env)
{
	(void) av;
	(void) env;
	(void) l_env;
	return (0);
}

int	is_in_child(int ret_value, int cmd_pid)
{
	if (cmd_pid == 0)
		return (8);
	else
		return (ret_value);
}
