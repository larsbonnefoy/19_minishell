/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_to_expender.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:33:52 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/09 12:31:46 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	lexer_to_expander(t_lexer *lexer, t_env **env)
{
	char	*clean;
	t_lexer	*head;

	head = lexer;
	while (lexer)
	{
		if (lexer->str)
		{
			//TODO $ARG="echo a" vs"$ARG" split then join or create node
			clean = cleaner(lexer->str, env);
			free(lexer->str);
			lexer->str = clean;
		}
		lexer = lexer->next;
	}
	lexer = head;
}
