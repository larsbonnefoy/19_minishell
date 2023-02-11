enum metacharacter
{
	pipe = '|' ,
	s_quote = 39,
	d_quote = 34,
	greater = '<',
	lower = '>',
};
	
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t	ft_strlen(char *str)
{
	int	i = -1;
	if (!str)
		return (-1);
	while (str[++i]);
	return (i);
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
 * returns the token ASCII value or 0 if its not a token
 */
int	is_token(int c)
{
	if (c == pipe)
		return (pipe);
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
 *
 */
char	*in_quotes(char *str, int *i, int quote_type)
{
	char	*res;

	if (!str)
		return (NULL);
	while (str[++(*i)])
		if (str[*i] == quote_type && *i != 0)
			return (ft_strldup(&str[1], *i - 1));
	return (NULL);
}

char	*expander(char *str)
{
	return (str);
	//TODO
}

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
			to_join = in_quotes(&str[i], &i, d_quote);
			//expander(to_join);
		}
		else if (str[i] == s_quote)
			to_join = in_quotes(&str[i], &i, s_quote);
		else
			to_join = ft_strldup(&str[i], 1);
		if (!to_join)
			return (NULL);
		tmp = cleaned;
		cleaned = ft_strjoin(cleaned, to_join);
		free(tmp);
		free(to_join);
	}
	return (cleaned);
}

int main()
{
	char sys_str[200] = "echo ";
	char test[] = "\"ec\"ho";
	
	char *clean = cleaner(test);
	printf("%s\n", clean);
	free(clean);
	strcat(sys_str, test);
	//system(sys_str);
	//system("leaks a.out");

}
