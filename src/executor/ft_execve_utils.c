/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:21:26 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/17 14:23:44 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"

static	int	is_in_child(int ret_value, int cmd_pid);

int	is_s_built(char *func_name, int cmd_pid)
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
	else if (is_local(func_name))
		return (8);
	return (-1);
}

int	ft_void(char **av, char ***env, t_env **l_env)
{
	(void) av;
	(void) env;
	(void) l_env;
	return (0);
}

static int	is_in_child(int ret_value, int cmd_pid)
{
	if (cmd_pid == 0)
		return (8);
	else
		return (ret_value);
}
