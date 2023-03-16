/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:37:01 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/16 17:25:47 by hdelmas          ###   ########.fr       */
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
		t_lexer **lexer, t_lexer **head, t_lexer **previous)
{
	char	**tab;
	int		j;
	t_lexer	*tmp;

	if (*to_join == '\0')
	{
		tmp = *lexer;
		if (!*previous)
			*head = (*lexer)->next;
		else 
			(*previous)->next = (*lexer)->next;
		*lexer = (*lexer)->next;
		free(tmp->str);
		tmp->str = NULL;
		free(tmp);
		return (to_join);
	}
	tab = ft_split(to_join, ' ');
	free(to_join);
	printf(">tab[%d] : [%s]\n", 0, tab[0]);
	j = -1;
	while (tab[++j])
	{
		printf(">tab[%d] : [%s]\n", j, tab[j]);
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
