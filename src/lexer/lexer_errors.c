/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:15:43 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/16 09:44:56 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static	int	is_redir(int token);

/*
 * checks for syntax errors in Lexer
 * Error if redir without arg before pipe
 * Invalid sequence | |, < |, | first, | last
 */
int	syntax_error(t_lexer **lexer)
{
	t_lexer	*curr;
	int		i;

	curr = *lexer;
	i = 0;
	while (curr)
	{
		if (curr->next)
		{
			if (is_redir(curr->token) && curr->next->token == PIPE)
				return (1);
			if (is_redir(curr->token) && is_redir(curr->next->token))
				return (1);
		}
		if (i == 0)
			if (curr->token == PIPE)
				return (1);
		if (curr->next == NULL)
			if (curr->token == PIPE)
				return (1);
		i++;
		curr = curr->next;
	}
	return (0);
}

int	is_redir(int token)
{
	if (token > PIPE && token <= D_LOWER)
		return (1);
	return (0);
}
