/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:43:08 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/17 14:03:31 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"

static void	set_exit_code(t_simple_cmds *cmd);

int	exec_alone_cmds(t_simple_cmds *cmd, t_fildes *fildes, t_envs *envs)
{
	if (handle_redir(cmd, fildes, envs->l_env) != 0)
	{
		restore_fildes(fildes);
		return (-1);
	}
	ft_execve(cmd, envs->env, envs->l_env);
	return (0);
}

int	exec_pipe_cmds(t_simple_cmds *cmd, t_fildes *fildes, t_envs *envs)
{
	t_simple_cmds	*curr;

	curr = cmd;
	while (curr)
	{
		if (curr->next != NULL)
		{
			if (pipe(fildes->fd_pipe) == -1)
				return (-1);
		}
		fildes->fd_in = process(curr, fildes, envs);
		curr = curr->next;
	}
	set_exit_code(cmd);
	return (0);
}

static void	set_exit_code(t_simple_cmds *cmd)
{
	t_simple_cmds	*curr;
	int				sig;

	curr = cmd;
	while (curr)
	{
		waitpid(curr->pid, &sig, 0);
		if (WIFSIGNALED(sig) && (g_ret_val != 130 && g_ret_val != 131))
			g_ret_val = WTERMSIG(sig);
		else if (WIFEXITED(sig) && (g_ret_val != 130 && g_ret_val != 131))
			g_ret_val = WEXITSTATUS(sig);
		curr = curr->next;
	}
}
