/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:57:34 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/13 14:56:28 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"

static	int	is_in_redir(t_lexer *redir);
static	int	open_redir(t_lexer *redir, int fd);

/*
 * opens fd of infile redirection if there is one, else returns fd_in
*/
int	get_in_fd(t_simple_cmds *cmd, int fd_in)
{
	t_lexer	*redir;
	int		fd;
	char	*file;

	redir = cmd->redirections;
	fd = -2;
	while (redir)
	{
		if (is_in_redir(redir))
			fd = open_redir(redir, fd);
		if (fd == -1)
			return (-1);
		redir = redir->next;
	}
	if (fd != -2)
	{
		close(fd_in);
		return (fd);
	}
	else
		return (fd_in);
}

static	int	open_redir(t_lexer *redir, int fd)
{
	if (fd != -2)
		close(fd);
	if (redir->token == LOWER)
	{
		fd = open(redir->str, O_RDONLY);
		if (fd == -1)
		{
			ft_perror(redir->str, NULL);
			return (-1);
		}
	}
	else
	{
		printf("exec heredoc");
	}
	return (fd);
}

static	int	is_in_redir(t_lexer *redir)
{
	if (redir->token == D_LOWER || redir->token == LOWER)
		return (1);
	return (0);
}

int	has_infile(t_lexer *redir)
{
	t_lexer	*curr_redir;

	curr_redir = redir;
	while (curr_redir)
	{
		if (is_in_redir(curr_redir) == 1)
			return (1);
		curr_redir = curr_redir->next;
	}
	return (0);
}
