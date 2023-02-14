/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smpcmd_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:32:14 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/14 22:05:04 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "smpcmd.h"
/* 
 * returns the token ASCII value or 0 if it's not a token
 */
// int	is_token(int c)
// {
// //	if (c == pipe)
// //		return (pipe);
// 	if (c == D_QUOTE)
// 		return (D_QUOTE);
// 	if (c == S_QUOTE)
// 		return (S_QUOTE);
// 	if (c == greater)
// 		return (greater);
// 	if (c == lower)
// 		return (lower);
// 	return (0);
// }

static char	*strcpy_in_quotes(char *str, int *i, int quote_type)
{
	int	tmp;

	if (!str || !i)
		return (NULL);
	tmp = *i;
	while (str[++(*i)])
		if (str[*i] == quote_type)
			return (ft_strldup(&str[tmp + 1], *i - tmp - 1));
	return (NULL);
}

/*
 * str is a string in quotes, i is the address of the position 
 * of the first character of str in the parent str.
 * quote_type is either " or '
 * the function returns the str without the enclosing quotes
 * if quote_type = -1 the function returns a sub str that stops
 * at the first quote in str or EOS
 */
static char	*in_quotes(char *str, int *i, int quote_type)
{
	char	*res;
	int		tmp;

	if (!str || !i)
		return (NULL);
	tmp = *i;
	if (quote_type > 0)
	{
		return (strcpy_in_quotes(str, i, quote_type));
	}
	else
	{
		while (str[++(*i)])
		{
			if ((str[*i] == D_QUOTE || str[*i] == S_QUOTE))
			{
				*i = *i - 1;
				return (ft_strldup(&str[tmp], *i - tmp + 1));
			}
		}
		*i = *i - 1;
		return (ft_strdup(&str[tmp]));
	}
	return (NULL);
}

static char	*expand(char *str, int *i, int quote_type, t_local **local_env)
{
	char	*to_join;
	char	*tmp;

	to_join = in_quotes(str, i, quote_type);
	tmp = to_join;
	to_join = expander(to_join, local_env);
	free(tmp);
	return (to_join);
}

/*
 * The cleaner function cleans str of every enclosing quote either " or '
 * and expand the enclosed values if they're in "
 * Cleaner returns the sanitized str
 */
char	*cleaner(char *str, t_local **local_env)
{
	int		i;
	char	*cleaned;
	char	*to_join;
	char	*tmp;

	if (!str)
		return (NULL);
	i = -1;
	cleaned = ft_calloc_exit(sizeof(char), 1);
	while (str[++i])
	{
		if (str[i] == D_QUOTE)
			to_join = expand(str, &i, D_QUOTE, local_env);
		else if (str[i] == S_QUOTE)
			to_join = in_quotes(str, &i, S_QUOTE);
		else
			to_join = expand(str, &i, -1, local_env);
		if (!to_join)
			return (NULL);
		tmp = cleaned;
		cleaned = ft_strjoin(cleaned, to_join);
		free(tmp);
		free(to_join);
	}
	return (cleaned);
}
