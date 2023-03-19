/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:37:01 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/17 11:28:42 by hdelmas          ###   ########.fr       */
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

static char	*set_check(char *to_join, t_prevhead *ph)
{
	ph->check = 1;
	return (to_join);
}

char	*no_quotes_handling(char *to_join, char **cleaned,
		t_lexer **lexer, t_prevhead *ph)
{
	char	**tab;
	int		j;
	t_lexer	*tmp;

	if (*to_join == '\0')
		return (set_check(to_join, ph));
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
