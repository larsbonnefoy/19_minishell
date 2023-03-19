/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_executor_handeling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:38:33 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/17 14:53:50 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"

int	open_heredoc(t_simple_cmds *cmd, int std_in, t_lexer *redir, t_env **l_env);

int	handle_heredoc(t_simple_cmds *cmd, int std_in, t_env **l_env)
{
	t_simple_cmds	*curr;
	t_lexer			*redir;
	int				tmp_std_in;

	curr = cmd;
	while (curr)
	{
		redir = curr->redirections;
		while (has_infile(redir))
		{
			if (redir->token == D_LOWER)
			{
				if (open_heredoc(curr, std_in, redir, l_env) == -1)
					return (-1);
			}	
			redir = redir->next;
		}
		curr = curr->next;
	}
	return (0);
}

int	open_heredoc(t_simple_cmds *cmd, int std_in, t_lexer *redir, t_env **l_env)
{	
	int	tmp_std_in;

	tmp_std_in = dup(std_in);
	if (tmp_std_in == -1)
		return (-1);
	if (cmd->hdoc_fd != -2)
		close(cmd->hdoc_fd);
	if (dup2(tmp_std_in, STDIN_FILENO) == -1)
		return (-1);
	cmd->hdoc_fd = ft_heredoc(redir->str, redir->hdoc_exp, l_env);
	close(tmp_std_in);
	if (cmd->hdoc_fd == -3)
		return (-1);
	return (0);
}
