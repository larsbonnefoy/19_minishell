/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:37:38 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/21 09:46:58 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../src/minishell.h"

t_simple_cmds	*simple_cmd(t_lexer *lexer)
{
	t_simple_cmds	*res;
	int				i;

	i = 0;

	res = ft_malloc(sizeof(t_simple_cmds));
	while (lexer && lexer->token != PIPE)
	{
		if (lexer->str)
		{
			res->av = ft_realloc((sizeof(char *) * i) + 1);
			res->av[i++] = lexer->str;
			lexer->str = NULL;
		}
		else
		{
			res->redirections = lexer;
			lexer = lexer->next;
			if (lexer && lexer->str)
			{
				res->redirections->str = lexer->str;
				lexer->str = NULL;
			}
		}
	lexer = lexer->next;
	}
	return (res);
}