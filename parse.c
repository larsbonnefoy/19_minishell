enum metacharacter
{
//	pipe = '|' ,
	s_quote = 39,
	d_quote = 34,
	greater = '<',
	lower = '>',
};
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

size_t	ft_strlen(char *str)
{
	int	i = -1;
	if (!str)
		return (-1);
	while (str[++i]);
	return (i);
}

char	*ft_strdup(char *s)
{
	int		len;
	int		i;
	char	*res;
	
	if (!s)
		return (NULL);
	len = -1;
	i = -1;
	while (s[++len])
		;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	while (s[++i])
	{
		res[i] = s[i];
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*strjoin;
	size_t	i;
	size_t	j;
	size_t	len_join;

	if (!s1 || !s2)
		return (NULL);
	len_join = ft_strlen(s1) + ft_strlen(s2);
	strjoin = malloc(sizeof(char) * (len_join + 1));
	if (!strjoin)
		return (NULL);
	i = 0;
	j = -1;
	while (s1[++j])
		strjoin[i++] = s1[j];
	j = -1;
	while (s2[++j])
		strjoin[i++] = s2[j];
	strjoin[i] = '\0';
	return (strjoin);
}

/*
 * strdup but either stop at the EOS or at max_len
 */
char	*ft_strldup(char *s, int max_len)
{
	int		len;
	int		i;
	char	*res;

	len = -1;
	i = -1;
	while (s[++len])
		;
	if (len > max_len)
		len = max_len;
	res = malloc(sizeof(char) * (len) + 1);
	if (!res)
		return (NULL);
	while (s[++i] && i < len)
	{
		res[i] = s[i];
	}
	res[i] = '\0';
	return (res);
}

/* 
 * returns the token ASCII value or 0 if it's not a token
 */
int	is_token(int c)
{
//	if (c == pipe)
//		return (pipe);
	if (c == d_quote)
		return (d_quote);
	if (c == s_quote)
		return (s_quote);
	if (c == greater)
		return (greater);
	if (c == lower)
		return (lower);
	return (0);
}

/*
 * str is a string in quotes, i is the address of the position 
 * of the first character of str in the parent str.
 * quote_type is either " or '
 * the function returns the str without the enclosing quotes
 * if quote_type = -1 the function returns a sub str that stops at the first quote in str or EOS
 */
char	*in_quotes(char *str, int *i, int quote_type)
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
			if ((str[*i] == d_quote || str[*i] == s_quote))
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
		if (str[i] == d_quote)
		{
			to_join = in_quotes(str, &i, d_quote);
			tmp = to_join;
			to_join = expander(to_join);
			free(tmp);
		}
		else if (str[i] == s_quote)
			to_join = in_quotes(str, &i, s_quote);
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

	line = readline("Sea-Shell>");

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

