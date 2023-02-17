/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smpcmd_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:01:36 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/17 09:50:08 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "smpcmd.h"

static char	*expand(char *str, t_local **local_env)
{
	char	*var;
	char	*to_join;

	if (!str)
		exit(EXIT_FAILURE);
	var = ft_get_local_env(str, local_env);
	if (var)
		return (ft_strdup(var));
	var = getenv(str);
	if (var)
		to_join = ft_strdup(var);
	else
		to_join = ft_strdup("");
	return (to_join);
}

static char	*handle_dollar(char *str, int *i, t_local **local_env)
{
	int		save_i;
	char	*tmp;
	char	*to_join;

	if (!str || !i)
		exit(EXIT_FAILURE);
	printf("in handle str = [%s]\n", str);
	if (str[++(*i)] == ' ' || str[*i] == '\0')
		to_join = ft_strldup(&str[*i - 1], 1);
	else if (ft_isdigit(str[*i]) || str[*i] == '?')
	{
		tmp = ft_strldup(&str[(*i)++], 1);
		to_join = expand(tmp, local_env);
		free(tmp);
	}
	else
	{
		save_i = *i;
		while (ft_isalnum(str[*i]))
			(*i)++;
		tmp = ft_strldup(&str[save_i], *i - save_i);
		to_join = expand(tmp, local_env);
		free(tmp);
	}
	return (to_join);
}

/*
 * expands $
 * TODO
 * local variable support
 * $? support
 * ~ idk if we need
 */
char	*expander(char *str, int quote_type, t_local **local_env)
{
	char	*expanded;
	char	*to_join;
	int		save_i;
	int		i;

	if (!str)
		exit(EXIT_FAILURE);
	i = 0;
	expanded = ft_calloc_exit(sizeof(char), 1);
	while (str[i])
	{
		save_i = i;
		while ((str[i] && str[i] != '$') || (quote_type == D_QUOTE
				&& str[i] == '$' && str[i + 1] == S_QUOTE))
			i++;
		to_join = ft_strldup(&str[save_i], i - save_i);
		expanded = ft_strjoin_ff(expanded, to_join);
		if (str[i] == '$')
		{
			to_join = handle_dollar(str, &i, local_env);
			expanded = ft_strjoin_ff(expanded, to_join);
		}
	}
	return (expanded);
}
