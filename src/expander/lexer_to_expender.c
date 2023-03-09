/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_to_expender.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:33:52 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/09 16:06:51 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expander.h"

void	lexer_to_expander(t_lexer *lexer, t_env **env)
{
	char	*clean;
	t_lexer	*head;

	head = lexer;
	while (lexer)
	{
		if (lexer->str)
			cleaner(&lexer, env);
		lexer = lexer->next;
	}
	lexer = head;
}
