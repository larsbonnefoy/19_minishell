/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:53:31 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/17 14:55:31 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"

static	int	is_out_redir(t_lexer *redirection);
static	int	open_redir(t_lexer *redir, int fd);

int	get_out_fd(t_simple_cmds *cmd, int pipe_write)
{
	int		fd;
	t_lexer	*redir;

	redir = cmd->redirections;
	fd = -2;
	while (redir)
	{
		if (is_out_redir(redir))
		{
			fd = open_redir(redir, fd);
			if (fd == -1)
				return (-1);
			if (cmd->next != NULL)
				close(pipe_write);
		}
		redir = redir->next;
	}
	if (fd != -2)
		return (fd);
	else
		return (pipe_write);
}

static	int	open_redir(t_lexer *redir, int fd)
{
	if (fd != -2)
		close(fd);
	if (redir->token == D_GREATER)
		fd = open(redir->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(redir->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_perror(redir->str, NULL, 1);
	return (fd);
}

/*
 * Returns 1 if t_lexer node is an out_redir
 * Else returns 0
 */
static	int	is_out_redir(t_lexer *redirection)
{
	if (redirection->token == D_GREATER || redirection->token == GREATER)
		return (1);
	return (0);
}

/*
 * Returns 1 for the first out_redir it finds in t_lexer redir
 * Else returns 0
 */
int	has_outfile(t_lexer *redirections)
{
	t_lexer	*curr_redir;

	curr_redir = redirections;
	while (curr_redir)
	{
		if (is_out_redir(curr_redir) == 1)
			return (1);
		curr_redir = curr_redir->next;
	}
	return (0);
}
