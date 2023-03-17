/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:57:34 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/17 14:36:41 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"

int	is_in_redir(t_lexer *redir);
int	open_redir(t_lexer *redir, int fd, t_env **l_env, t_simple_cmds *cmd);
int	is_last_infile(t_lexer *redir);

int	get_in_fd(t_simple_cmds *cmd, int fd_in, t_env **l_env)
{
	t_lexer	*redir;
	int		fd;
	char	*file;

	redir = cmd->redirections;
	fd = -2;
	while (redir)
	{
		if (is_in_redir(redir))
			fd = open_redir(redir, fd, l_env, cmd);
		if (fd == -1)
		{
			ft_perror(redir->str, NULL, 1);
			return (-1);
		}
		redir = redir->next;
	}
	if (fd != -2)
		return (fd);
	else
		return (fd_in);
}

int	open_redir(t_lexer *redir, int fd, t_env **l_env, t_simple_cmds *cmd)
{
	if (fd != -2)
		close(fd);
	if (redir->token == LOWER)
		fd = open(redir->str, O_RDONLY);
	if (is_last_infile(redir) && redir->token == D_LOWER)
		fd = cmd->hdoc_fd;
	if (is_last_infile(redir) && redir->token == LOWER && cmd->hdoc_fd != -2)
		close(cmd->hdoc_fd);
	return (fd);
}

int	is_last_infile(t_lexer *redir)
{
	t_lexer	*tmp_redir;

	tmp_redir = redir;
	while (tmp_redir)
	{
		if (tmp_redir->next)
		{
			if (is_in_redir(tmp_redir->next))
				return (0);
		}
		tmp_redir = tmp_redir->next;
	}
	return (1);
}

int	is_in_redir(t_lexer *redir)
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
