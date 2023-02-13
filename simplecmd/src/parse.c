/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:32:14 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/13 14:50:40 by hdelmas          ###   ########.fr       */
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

/*
 * str is a string in quotes, i is the address of the position 
 * of the first character of str in the parent str.
 * quote_type is either " or '
 * the function returns the str without the enclosing quotes
 * if quote_type = -1 the function returns a sub str that stops
 * at the first quote in str or EOS
 */

static char	*strcpy_in_quotes(char *str, int *i, int quote_type)
{
	int	tmp;

	tmp = *i;
	while (str[++(*i)])
		if (str[*i] == quote_type)
			return (ft_strldup(&str[tmp + 1], *i - tmp - 1));
	return (NULL);
}

static char	*in_quotes(char *str, int *i, int quote_type)
{
	char	*res;
	int		tmp;

	if (!str)
		return (NULL);
	tmp = *i;
	if (quote_type > 0)
	{
		strcpy_in_quotes(str, i, quote_type);
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

/*
 * expands $
 * local variable suport to add
 * $? suport to add 
 * ~ idk if we need
 */
char	*expander(char *str)
{
	char	*expanded;
	char	*to_join;
	char	*tmp;
	char	*var;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	expanded = malloc(sizeof(char) + 1);
	if (!expanded)
		return (NULL);
	expanded[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[++i] == ' ')
				to_join = ft_strldup(&str[i - 1], 1);
			if (str[i] == '\0')
				to_join = ft_strldup(&str[i - 1], 1);
			else
			{
				var = malloc(sizeof(char) + 1);
				if (!var)
					return (NULL);
				var[0] = '\0';
				while (str[i] != ' ' && str[i] != '\0')
				{
					tmp = var;
					to_join = ft_strldup(&str[i], 1);
					var = ft_strjoin(var, to_join);
					free(to_join);
					free(tmp);
					i++;
				}
				to_join = ft_strdup(getenv(var));
				free(var);
				if (!to_join)
					to_join = ft_strdup("");
			}
			tmp = expanded;
			expanded = ft_strjoin(expanded, to_join);
			free(tmp);
			free(to_join);
		}
		else
		{
			tmp = expanded;
			to_join = ft_strldup(&str[i], 1);
			expanded = ft_strjoin(expanded, to_join);
			free(tmp);
			free(to_join);
			i++;
		}
	}
	return (expanded);
}

char	*expand(char *str, int *i, int quote_type)
{
	char	*to_join;
	char	*tmp;

	to_join = in_quotes(str, i, quote_type);
	tmp = to_join;
	to_join = expander(to_join);
	free(tmp);
	return (to_join);
}

/*
 * The cleaner function cleans str of every enclosing quote either " or '
 * and expand the enclosed values if they're in "
 * Cleaner returns the sanitized str
 */
char	*cleaner(char *str)
{
	int		i;
	char	*cleaned;
	char	*to_join;
	char	*tmp;

	if (!str)
		return (NULL);
	i = -1;
	cleaned = malloc(sizeof(char) + 1);
	if (!cleaned)
		return (NULL);
	cleaned[0] = '\0';
	while (str[++i])
	{
		if (str[i] == D_QUOTE)
			to_join = expand(str, &i, D_QUOTE);
		else if (str[i] == S_QUOTE)
			to_join = in_quotes(str, &i, S_QUOTE);
		else
			to_join = expand(str, &i, -1);
		if (!to_join)
			return (NULL);
		tmp = cleaned;
		cleaned = ft_strjoin(cleaned, to_join);
		free(tmp);
		free(to_join);
	}
	return (cleaned);
}
