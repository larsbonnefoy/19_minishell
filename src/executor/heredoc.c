/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:44:31 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/13 11:29:54 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"
#include "../../Includes/minishell.h"
#include "../../Includes/prompt.h"

int	ft_heredoc(char *limiter, int expand, t_env **l_env)
{
	int		fd_pipe[2];
	char	*line;
	char	*tmp;
	char	*to_write;

	if (pipe(fd_pipe) == -1)
		return (1);
	to_write = ft_calloc_exit(sizeof(char), 1);
	while (1)
	{
		line = readline("\033[0;35mHEREDOC>\033[0m");
		printf("print>[%s]\n", line);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		if (expand == 1)
		{
			tmp = line;
			line = expander(line, -1, l_env);
			free(tmp);
		}
		line = ft_strjoin(line, "\n");
		to_write = ft_strjoin_ff(to_write, line);
	}
	dup2(fd_pipe[0], STDIN_FILENO);
	write(fd_pipe[1], to_write, ft_strlen(to_write));
	close(fd_pipe[1]);
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
