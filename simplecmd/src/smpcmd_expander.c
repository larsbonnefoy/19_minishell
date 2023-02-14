/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smpcmd_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:01:36 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/14 12:01:51 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "smpcmd.h"

static char	*expand(char *str)
{
	char	*var;
	char	*to_join;

	if (!str)
		exit(EXIT_FAILURE);
	var = getenv(str);
	if (var)
		to_join = ft_strdup(var);
	else
		to_join = ft_strdup("");
	return (to_join);
}

static char	*handle_dollar(char *str, int *i)
{
	int		save_i;
	char	*tmp;
	char	*to_join;

	if (!str || !i)
		exit(EXIT_FAILURE);
	if (str[++(*i)] == ' ' || str[*i] == '\0')
		to_join = ft_strldup(&str[*i - 1], 1);
	else
	{
		save_i = *i;
		while (str[*i] != ' ' && str[*i] != '\0' && str[*i] != '$')
			(*i)++;
		tmp = ft_strldup(&str[save_i], *i - save_i);
		to_join = expand(tmp);
		free(tmp);
	}
	return (to_join);
}

static char	*ft_strjoin_free(char *str1, char *str2)
{
	char	*res;

	if (!str1 || !str2)
		exit(EXIT_FAILURE);
	res = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (res);
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
	int		save_i;
	int		i;

	if (!str)
		exit(EXIT_FAILURE);
	i = 0;
	expanded = ft_calloc_exit(sizeof(char), 1);
	while (str[i])
	{
		save_i = i;
		while (str[i] && str[i] != '$')
			i++;
		to_join = ft_strldup(&str[save_i], i - save_i);
		expanded = ft_strjoin_free(expanded, to_join);
		if (str[i] == '$')
		{
			to_join = handle_dollar(str, &i);
			expanded = ft_strjoin_free(expanded, to_join);
		}
	}
	return (expanded);
}
