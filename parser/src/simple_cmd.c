/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:37:38 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/22 13:31:30 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_simple_cmds	*create_simple_cmd(t_lexer *lexer)
{
	t_simple_cmds	*res;
	t_lexer			*tmp;
	int				i;

	i = 0;
	res = ft_malloc(sizeof(t_simple_cmds));
	res->av = NULL;
	res->redirections = NULL;
	res->next = NULL;
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->str)
		{
			res->av = (char **)ft_realloc_tab((void *)res->av, (sizeof(char *) * (i + 1)), i + 1);
			res->av[i] = lexer->str;
			res->av[++i] = NULL;
			lexer->str = NULL;
		}
		else
		{
			res->redirections = lexer;
			lexer = lexer->next;
			if (!lexer)
				return (res);
			if (lexer->str)
			{
				res->redirections->str = lexer->str;
				lexer->str = NULL;
			}	
		}
	tmp = lexer;
	lexer = lexer->next;
	if (tmp->str)
		free(tmp->str);
	free(tmp);
	}
	return (res);
}

void	destroy_simple_cmd(t_simple_cmds *cmd)
{
	int				i;
	t_simple_cmds	*tmp;

	i = -1;
	while (cmd)
	{
		while (cmd->av && cmd->av[++i])
			free(cmd->av[i]);
		if (cmd->av)
			free(cmd->av);
		lexer_clear_list(&cmd->redirections);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}