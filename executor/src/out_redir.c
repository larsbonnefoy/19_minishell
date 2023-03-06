/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:53:31 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/06 10:56:31 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int get_out_fd(t_simple_cmds *cmd, int pipe_write)
{
	char	*file;
	int		token;
	int		fd;

	if (is_outfile(cmd->redirections))
	{
		file = get_out_file(cmd);	
		token = get_out_token(cmd, file);
		if (token == D_GREATER)
			fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{	
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (cmd->next != NULL)
			close(pipe_write);
		printf("opened %s on %d\n", file, fd);
		return (fd);
	}
	else
		return (pipe_write);
}

char *get_out_file(t_simple_cmds *cmd)
{
	t_lexer *redir;
	char	*file;

	redir = cmd->redirections;
	file = NULL;
	while (redir)
	{
		if (redir->token == GREATER || redir->token == D_GREATER)
			file = redir->str;
		redir = redir->next;
	}
	return (file);
}

int get_out_token(t_simple_cmds *cmd, char *file)
{
	int token;
	t_lexer	*redir;

	redir = cmd->redirections;
	while(redir)
	{
		if (file == redir->str)
			token = redir->token;
		redir = redir->next;
	}
	return (token);
}

int is_outfile(t_lexer *redirections)
{
	t_lexer *curr_redir;
	curr_redir = redirections;
	while (curr_redir)
	{
		if (curr_redir->token == D_GREATER || curr_redir->token == GREATER)
			return (1);
		curr_redir=curr_redir->next;
	}
	return (0);
}
