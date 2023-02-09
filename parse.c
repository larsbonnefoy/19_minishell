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
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	printf("len %d\n",len);
	while (s[++i] && i < len)
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

char	*in_d_quotes(char *str)
{
	char	*res;
	int		i;
	int		nbr_d_quote;

	i = -1;
	if (!str)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == d_quote)
			return (ft_strldup(&str[1], i));
	}
	if (i == strlen(str))
		return (NULL);
	res = ft_strldup(&str[1], i); 
	return (NULL);
}

int main()
{
	char sys_str[200] = "echo ";
	char test[] = "\"\'\"4444\"\"";
	
	printf("%s\n", in_d_quotes(test));
	strcat(sys_str, test);
	system(sys_str);

}
