/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:32:14 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/13 09:03:37 by hdelmas          ###   ########.fr       */
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
 * if quote_type = -1 the function returns a sub str that stops at the first quote in str or EOS
 */
static char	*in_quotes(char *str, int *i, int quote_type)
{
	char	*res;
	int		tmp;

	if (!str)
		return (NULL);
	tmp = *i;
	if (quote_type > 0)
	{
		while (str[++(*i)])
			if (str[*i] == quote_type && *i != tmp)
				return (ft_strldup(&str[tmp + 1], *i - tmp - 1));
	}
	else
	{
		while (str[++(*i)])
			if ((str[*i] == D_QUOTE || str[*i] == S_QUOTE))
				return (ft_strldup(&str[tmp], *i - tmp - 1));
		*i = *i - 1;
		return (ft_strdup(str));
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
	i  = 0;
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
					to_join =ft_strdup("");
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
		{
			to_join = in_quotes(str, &i, D_QUOTE);
			tmp = to_join;
			to_join = expander(to_join);
			free(tmp);
		}
		else if (str[i] == S_QUOTE)
			to_join = in_quotes(str, &i, S_QUOTE);
		else
		{
			to_join = in_quotes(str, &i, -1);
			tmp = to_join;
			to_join = expander(to_join);
			free(tmp);
		}
		if (!to_join)
			return (NULL);
		tmp = cleaned;
		cleaned = ft_strjoin(cleaned, to_join);
		free(tmp);
		free(to_join);
	}
	return (cleaned);
}

char *get_line(void)
{
	char *line;

	line = readline("\033[0;36mSea-Shell>\033[0m");

	return (line);
}

int main(int argc, char **argv, char **env)
{
	char *line;
	char *clean;
	(void) argc;
	(void) argv;
	int	i =-1;
//	while (env[++i])
//		printf("%s\n",env[i]);
	//printf("%s\n",getenv("?"));
	while (1)
	{
		char sys_str[200] = "echo echo :";
		line = get_line();
		clean = cleaner(line);
		printf("input :%s\n", line);
		printf("cleaned :%s\n", clean);
		free(clean);
		strcat(sys_str, line);
		system(sys_str);
		free(line);
	}
	return(0);
}

