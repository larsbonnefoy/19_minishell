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
	res = malloc(sizeof(char) * (len));
	if (!res)
		return (NULL);
	printf("len %d\n",len);
	while (s[++i] && i < len - 1)
	{
		res[i] = s[i];
	}
	res[i] = '\0';
	return (res);
}

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

char	*in_quotes(char *str, int *i, int quote_type)
{
	char	*res;

	if (!str)
		return (NULL);
	while (str[++(*i)])
		if (str[*i] == quote_type && *i != 0)
			return (ft_strldup(&str[1], *i));
	return (NULL);
}

char	*expender(char *str)
{
	return (str);
	//TODO
}

/*
* arg_parser take a string as input, following the argv syntax but as a long string. 
* eg : CMD_NAME arg1 arg2 ...etc
* The function divide the input string at every Space (" ") into smallers words, 
* remove quotes characters and expand variables if needed using the funtion cleaner and expender
* It returns the list of every new strings in order of appearance in the original string
* eg : {"CMD_NAME", "arg1", "arg2", ...} 
*
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
	cleaned = malloc(sizeof(char));
	if (!cleaned)
		return (NULL);
	cleaned =  "";
	while (str[++i])
	{
		printf("str[i] = %c\n", str[i]);
		if (str[i] == d_quote)
			to_join = in_quotes(&str[i], &i, d_quote);
		else if (str[i] == s_quote)
			to_join = in_quotes(&str[i], &i, s_quote);
		else
			to_join = ft_strldup(&str[i], 1);
		if (!to_join)
			return (NULL);
		tmp = cleaned;
		cleaned = ft_strjoin(tmp, to_join);
		free(tmp);
		free(to_join);
	}
	return (cleaned);
}

int main()
{
	char sys_str[200] = "echo ";
	char test[] = "'$PATH'";
	
	printf("i prev = %d \n%s\n i = %d\n", 1, cleaner(test), 1);
	strcat(sys_str, test);
	system(sys_str);

}
