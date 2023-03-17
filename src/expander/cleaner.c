/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:32:14 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/17 11:21:41 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/expander.h"

/*
 * str is a string in quotes, i is the address of the position 
 * of the first character of str in the parent str.
 * quote_type is either " or '
 * the function returns the str without the enclosing quotes
 */
char	*strdup_in_quotes(char *str, int *i, int quote_type)
{
	int	tmp;

	if (!str || !i)
		exit(EXIT_FAILURE);
	tmp = *i;
	while (str[++(*i)])
		if (str[*i] == quote_type)
			return (ft_strldup(&str[tmp + 1], *i - tmp - 1));
	exit(EXIT_FAILURE);
	return (NULL);
}

char	*dup_word(char *str, int *i)
{
	int		tmp;

	if (!str || !i)
		exit(EXIT_FAILURE);
	tmp = *i;
	while (str[++(*i)])
	{
		if (!ft_isalnum(str[*i]) && *i != tmp && str[*i] != '?')
		{
			*i = *i - 1;
			return (ft_strldup(&str[tmp], *i - tmp + 1));
		}
		else if ((ft_isdigit(str[*i]) || str[*i] != '?') && *i == tmp)
		{
			*i = *i - 1;
			return (ft_strldup(&str[tmp], *i - tmp + 1));
		}
	}
	*i = *i - 1;
	return (ft_strdup(&str[tmp]));
}

static char	*to_expand(char *str, int *i, int quote_type, t_env **local_env)
{
	char	*to_join;
	char	*tmp;

	if (str[*i] == '$' && (str[*i + 1] == 34 || str[*i + 1] == 39))
		return (ft_strdup(""));
	if (quote_type == -1)
		tmp = dup_word(str, i);
	else
		tmp = strdup_in_quotes(str, i, quote_type);
	printf(">[%s]\n", tmp);
	to_join = expander(tmp, quote_type, local_env);
	free(tmp);
	return (to_join);
}

char	*while_str(char *str, t_lexer **lexer,
		t_env **local_env, t_prevhead *ph)
{
	char	*to_join;
	int		i;
	char	*cleaned;

	i = -1;
	cleaned = ft_calloc_exit(sizeof(char), 1);
	while (str[++i])
	{
		if (str[i] == D_QUOTE)
			to_join = to_expand(str, &i, D_QUOTE, local_env);
		else if (str[i] == S_QUOTE)
			to_join = strdup_in_quotes(str, &i, S_QUOTE);
		else
		{
			ph->check = 0;
			to_join = to_expand(str, &i, -1, local_env);
			to_join = no_quotes_handling(to_join, &cleaned, lexer, ph);
		}
		cleaned = ft_strjoin_ff(cleaned, to_join);
	}
	return (cleaned);
}

/*
 * The cleaner function cleans str of every enclosing quote either " or '
 * and expand the enclosed values if they're in "
 * Cleaner returns the sanitized str
 */
void	cleaner(t_lexer **lexer, t_env **local_env, t_prevhead *ph)
{
	char	*cleaned;
	char	*str;
	t_lexer	*save_head;
	t_lexer	*save_next;

	if (!lexer || !*lexer)
		exit(EXIT_FAILURE);
	if (!(*lexer)->str)
		return ;
	save_next = (*lexer)->next;
	save_head = ph->head;
	str = ft_strdup((*lexer)->str);
	cleaned = while_str(str, lexer, local_env, ph);
	free(str);
	(*lexer)->next = save_next;
	free((*lexer)->str);
	(*lexer)->str = cleaned;
	return ;
}
