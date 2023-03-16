/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:37:01 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/16 23:31:59 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expander.h"

static void	lexer_insert(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = lexer_new_node(NULL, 0);
	(*lexer)->next = tmp;
	*lexer = tmp;
}

char	*no_quotes_handling(char *to_join, char **cleaned,
		t_lexer **lexer, t_prevhead *ph)
{
	char	**tab;
	int		j;
	t_lexer	*tmp;

	if (*to_join == '\0')
	{
		tmp = *lexer;
		if (!ph->prev)
			ph->head = (*lexer)->next;
		else
		{
			(ph->prev)->next = (*lexer)->next;
		printf("hmmm>%s>\n",ph->prev->str);
		}
		ph->check = 1;
		// *lexer = (*lexer)->next;
		// free(tmp->str);
		// tmp->str = NULL;
		// free(tmp);
		return (to_join);
	}
	tab = ft_split(to_join, ' ');
	free(to_join);
	j = -1;
	while (tab[++j])
	{
		if (j == 0)
			to_join = tab[j];
		else
		{
			free((*lexer)->str);
			(*lexer)->str = ft_strjoin_ff(*cleaned, to_join);
			*cleaned = ft_strdup("");
			lexer_insert(lexer);
			to_join = tab[j];
		}
	}
	free(tab);
	return (to_join);
}
