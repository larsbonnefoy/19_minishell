/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:09:41 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/17 14:35:29 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"

int	create_struct(t_fildes *fildes, t_envs *envs, char ***env, t_env **l_env);

void	executor(t_simple_cmds *cmd, char ***env, t_env **l_env)
{
	t_simple_cmds	*curr;
	t_fildes		fildes;
	t_envs			envs;

	if (!cmd)
		return ;
	create_struct(&fildes, &envs, env, l_env);
	curr = cmd;
	if (handle_heredoc(cmd, fildes.std_in, l_env) == -1)
	{
		restore_fildes(&fildes);
		return ;
	}
	if (curr->next == NULL && !curr->av)
		handle_redir(curr, &fildes, l_env);
	else
	{
		if ((curr->next == NULL && is_s_built(curr->av[0], curr->pid) != -1))
			exec_alone_cmds(cmd, &fildes, &envs);
		else
			exec_pipe_cmds(curr, &fildes, &envs);
	}
	restore_fildes(&fildes);
}

int	process(t_simple_cmds *cmd, t_fildes *fildes, t_envs *envs)
{
	int	fd_out;

	handle_signal(4);
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		ft_perror("fork", NULL, 1);
		return (-1);
	}
	if (cmd->pid == 0)
	{
		handle_signal(3);
		if (handle_redir(cmd, fildes, envs->l_env) != 0)
			exit(EXIT_FAILURE);
		if (cmd->av)
			ft_execve(cmd, envs->env, envs->l_env);
		exit(g_ret_val);
	}
	if (cmd->n > 0)
		close(fildes->fd_in);
	close(fildes->fd_pipe[1]);
	close(cmd->hdoc_fd);
	return (fildes->fd_pipe[0]);
}

int	handle_redir(t_simple_cmds *cmd, t_fildes *fildes, t_env **l_env)
{	
	if (cmd->n > 0 || has_infile(cmd->redirections))
	{
		fildes->fd_in = get_in_fd(cmd, fildes->fd_in, l_env);
		if (fildes->fd_in == -1)
			return (-1);
		if (dup2(fildes->fd_in, STDIN_FILENO) == -1)
			return (-1);
		if (close(fildes->fd_in) == -1)
			ft_perror("close", NULL, 1);
	}
	if (cmd->next != NULL || has_outfile(cmd->redirections))
	{
		fildes->fd_pipe[1] = get_out_fd(cmd, fildes->fd_pipe[1]);
		if (fildes->fd_pipe[1] == -1)
			return (-1);
		if (dup2(fildes->fd_pipe[1], STDOUT_FILENO) == -1)
			return (-1);
		if (cmd->next != NULL)
			close(fildes->fd_pipe[0]);
		close(fildes->fd_pipe[1]);
	}
	return (0);
}

int	create_struct(t_fildes *fildes, t_envs *envs, char ***env, t_env **l_env)
{
	fildes->fd_in = STDIN_FILENO;
	fildes->fd_pipe[0] = -1;
	fildes->fd_pipe[1] = -2;
	fildes->std_in = dup(STDIN_FILENO);
	fildes->std_out = dup(STDOUT_FILENO);
	if (fildes->std_in == -1 || fildes->std_out == -1)
	{
		ft_perror("dup", NULL, 1);
		exit(EXIT_FAILURE);
	}
	envs->env = env;
	envs->l_env = l_env;
	return (0);
}

void	restore_fildes(t_fildes *fildes)
{
	if (dup2(fildes->std_in, STDIN_FILENO) == -1)
		return (exit(EXIT_FAILURE));
	if (dup2(fildes->std_out, STDOUT_FILENO) == -1)
		return (exit(EXIT_FAILURE));
	close(fildes->std_out);
	close(fildes->std_in);
}
