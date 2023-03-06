/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:57:34 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/06 11:00:38 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "executor.h"

/*
 * opens fd of infile redirection if there is one, else returns fd_in
*/
int get_in_fd(t_simple_cmds *cmd,int fd_in)
{
	t_lexer *redir; 	
	int 	fd;
	char 	*file;
	
	redir = cmd->redirections;
	file = NULL;
	while (redir)
	{
		if (redir->token == LOWER)
			file = redir->str;
		redir=redir->next;
	}
	if (file)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			perror("open");
		close(fd_in);
		return (fd);
	}
	return (fd_in);
}

int is_infile(t_lexer *redirection)
{
	t_lexer *curr_redir;
	curr_redir = redirection;
	while (curr_redir)
	{
		if (curr_redir->token == LOWER)
			return (1);
		curr_redir=curr_redir->next;
	}
	return (0);
}
