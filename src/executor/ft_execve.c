/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:27:03 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/17 14:26:37 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"

char	*get_access_path(char **av, char *path);
int		access_exec(char *access_path, t_simple_cmds *cmd, char ***env);
int		exec_s_built(char **av, char ***env, t_env **l_env, int self_built_nb);
void	exec_n_built(t_simple_cmds *cmd, char ***env, t_env **l_env);

void	ft_execve(t_simple_cmds *cmd, char ***env, t_env **l_env)
{
	int		self_builtin_nb;

	if (is_local(cmd->av[0]))
		cmd->av = make_local(cmd->av);
	self_builtin_nb = is_s_built(cmd->av[0], cmd->pid);
	if (self_builtin_nb != -1)
		g_ret_val = exec_s_built(cmd->av, env, l_env, self_builtin_nb);
	else
		exec_n_built(cmd, env, l_env);
}

void	exec_n_built(t_simple_cmds *cmd, char ***env, t_env **l_env)
{
	char	**path_arr;
	char	*access_path;
	int		i;

	if (ft_strchr(cmd->av[0], '/') != NULL)
		access_exec(cmd->av[0], cmd, env);
	else
	{
		if (!ft_getenv("PATH", l_env))
			exit(ft_perror(cmd->av[0], ": command not found", 127));
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
	exit(ft_perror(cmd->av[0], ": command not found", 127));
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
