/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_to_expender.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:33:52 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/17 10:14:00 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expander.h"

static char	*clean_doc(t_lexer *lexer)
{
	char	*to_join;
	char	*cleaned;
	char	*str;
	int		i;

	i = -1;
	str = lexer->str;
	cleaned = ft_calloc_exit(sizeof(char), 1);
	while (str[++i])
	{
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
		{
			to_join = strdup_in_quotes(str, &i, str[i]);
			lexer->hdoc_exp = 0;
		}
		else
			to_join = dup_word(str, &i);
		cleaned = ft_strjoin_ff(cleaned, to_join);
	}
	free(str);
	return (cleaned);
}

static void	handle_doc(t_lexer *lexer, t_lexer *next)
{
	lexer->hdoc_exp = 1;
	lexer->str = next->str;
	lexer->next = next->next;
	free(next);
	lexer->str = clean_doc(lexer);
}

void	lexer_to_expander(t_lexer **lexer, t_env **env)
{
	char		*clean;
	t_lexer		*tmp;
	t_prevhead	ph;

	ph.head = (*lexer);
	ph.prev = NULL;
	while ((*lexer))
	{
		ph.check = 0;
		printf(">>>>[%s] \n", (*lexer)->str);
		if ((*lexer)->str)
			cleaner(lexer, env, &ph);
		else if ((*lexer)->token == D_LOWER)
		{
			tmp = (*lexer)->next;
			if (tmp && tmp->str)
				handle_doc((*lexer), tmp);
			else
			{
				ft_putstr_fd("parse error", 2);
				exit(1);
			}
		}
		tmp = (*lexer);
		if (ph.check && (*lexer)->str[0] == '\0')
		{
			if (!ph.prev)
				ph.head = (*lexer)->next;
			else
			{
				(ph.prev)->next = (*lexer)->next;
			}
			free(tmp->str);
			tmp->str = NULL;
			free(tmp);
		}
		else
			ph.prev = (*lexer);
		if ((*lexer))
			(*lexer) = (*lexer)->next;
	}
	(*lexer) = ph.head; 
}
