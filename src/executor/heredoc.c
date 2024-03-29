/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:15:08 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/20 16:45:02 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"
#include "../../Includes/global.h"

static void	here_err(char *limiter)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: here-document by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
}

static char	*joinback_n(char *to_write, char *save)
{
	char	*tmp;

	tmp = ft_strjoinf(save, "\n");
	to_write = ft_strjoin_ff(to_write, tmp);
	return (to_write);
}

static int	write_to_pipe(char *to_write, int fd_pipe)
{
	write(fd_pipe, to_write, ft_strlen(to_write));
	close(fd_pipe);
	exit(EXIT_SUCCESS);
}

static int	here_child(int fd_pipe[2], char *limiter, int expand, t_env **l_env)
{
	char	*line;
	char	*save;
	char	*to_write;

	close(fd_pipe[0]);
	to_write = ft_calloc_exit(sizeof(char), 1);
	while (1)
	{
		handle_signal(1);
		line = readline("\033[0;35mHEREDOC>\033[0m");
		if (!line)
		{
			here_err(limiter);
			break ;
		}
		if (line && ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		if (expand == 1)
			save = expander(line, -1, l_env);
		else
			save = ft_strdup(line);
		to_write = joinback_n(to_write, save);
	}
	write_to_pipe(to_write, fd_pipe[1]);
	exit(EXIT_SUCCESS);
}

int	ft_heredoc(char *limiter, int expand, t_env **l_env)
{
	int		fd_pipe[2];
	int		pid;
	int		child_ret;

	g_ret_val = 0;
	handle_signal(2);
	if (pipe(fd_pipe) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		here_child(fd_pipe, limiter, expand, l_env);
	close(fd_pipe[1]);
	waitpid(pid, &child_ret, 0);
	if (g_ret_val == 130)
	{
		close(fd_pipe[0]);
		return (-3);
	}
	if (WIFSIGNALED(child_ret))
		g_ret_val = WTERMSIG(child_ret);
	else
		g_ret_val = WEXITSTATUS(child_ret);
	return (fd_pipe[0]);
}

// int main(void)
// {
// 	int	std_in = dup(STDIN_FILENO);
// 	int	std_out = dup(STDOUT_FILENO);

// 	t_heredoc *heredoc;
// 	heredoc->limiter = "EOF";
// 	heredoc->expand = 0;
// 	ft_heredoc(heredoc);
// 	dup2(std_in, STDIN_FILENO);
// 	dup2(std_out, STDOUT_FILENO);
// 	close(std_out);
// 	close(std_in);
// } 
