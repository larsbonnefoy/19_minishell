/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:44:31 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/14 09:35:06 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"
#include "../../Includes/minishell.h"
#include "../../Includes/prompt.h"

static int	here_err(char *limiter)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: here-document by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putendl_fd("')", 2);
	return (-2);
}

static char	*joinback_n(char *to_write, char *save)
{
	char	*tmp;

	tmp = ft_strjoin(save, "\n");
	to_write = ft_strjoin_ff(to_write, tmp);
	return (to_write);
}

static int	write_to_pipe(char *to_write)
{
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (1);
	dup2(fd_pipe[0], STDIN_FILENO);
	write(fd_pipe[1], to_write, ft_strlen(to_write));
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}

int	ft_heredoc(char *limiter, int expand, t_env **l_env)
{
	char	*line;
	char	*save;
	char	*to_write;

	to_write = ft_calloc_exit(sizeof(char), 1);
	while (1)
	{
		line = readline("\033[0;35mHEREDOC>\033[0m");
		if (!line)
			here_err(limiter);
		if (line && ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		if (expand == 1)
			save = expander(line, -1, l_env);
		else
			save = ft_strdup(line);
		to_write = joinback_n(to_write, save);
	}
	return (write_to_pipe(to_write));
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
