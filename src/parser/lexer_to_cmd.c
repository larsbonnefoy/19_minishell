/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:05:16 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/13 22:07:49 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

static void	lexer_to_heredoc(t_lexer **lexer, t_simple_cmds *res)
{
	t_lexer			*tmp;

	if ((*lexer)->str)
	{
		tmp = lexer_new_node(ft_strdup((*lexer)->str), (*lexer)->token);
		tmp->hdoc_exp = (*lexer)->hdoc_exp;
		lexer_add_back(&res->redirections, tmp);
	}
}

static int	lexer_to_redir(t_lexer **lexer, t_simple_cmds *res, int i)
{
	t_lexer			*tmp;

	tmp = lexer_new_node(NULL, (*lexer)->token);
	lexer_add_back(&res->redirections, tmp);
	*lexer = (*lexer)->next;
	if (!*lexer)
		return (i);
	if ((*lexer)->str)
	tmp->str = ft_strdup((*lexer)->str);
	return (i);
}

int	lexer_to_cmd(t_lexer **lexer, t_simple_cmds *res, int i)
{
	t_lexer			*tmp;

	if (!lexer)
		exit(EXIT_FAILURE);
	if ((*lexer)->str && (*lexer)->token == NOT_A_TOKEN)
	{
		res->av = (char **)ft_realloc_tab((void *)res->av,
				(sizeof(char *)), i + 1);
		res->av[i] = ft_strdup((*lexer)->str);
		res->av[++i] = NULL;
	}
	else if ((*lexer)->token != D_LOWER)
		i = lexer_to_redir(lexer, res, i);
	else
		lexer_to_heredoc(lexer, res);
	return (i);
}
