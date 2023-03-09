/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:44:31 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/09 11:49:00 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../Includes/executor.h"


typedef struct s_heredoc
{
	char	*limiter;
	int		expand;
} t_heredoc;


int	ft_heredoc(t_heredoc *heredoc)
{
	int		fd_pipe[2];
	char	*line;

	if (pipe(fd_pipe) == -1)
		return (1); //some error
	dup2(fd_pipe[0], STDIN_FILENO);
	while (1)
	{
		line = readline(">");
		if (ft_strncmp(line, heredoc->limiter, ft_strlen(heredoc->limiter) + 1))
			break;
		if (heredoc->expand == 1)
			line = "exp"; 
		write(fd_pipe[1], line, ft_strlen(line));
	}
	return (fd_pipe[0]);
}


int main()
{
	int std_in = dup(STDIN_FILENO);
	int	std_out = dup(STDOUT_FILENO);

	t_heredoc *heredoc;

	heredoc->limiter = "EOF";
	heredoc->expand = 0;
	ft_heredoc(heredoc);
	
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_out);
	close(std_in);

} 
