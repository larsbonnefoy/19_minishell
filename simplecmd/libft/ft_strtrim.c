/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:07:48 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 10:00:24 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

static size_t	words_len(char const *s1, char const *set, size_t *s, size_t *e)
{
	size_t	i;
	size_t	str_len;

	i = 0;
	str_len = ft_strlen(s1);
	while (is_set(s1[i], set) == 1 && s1[i])
		++i;
	*s = i;
	i = str_len - 1;
	while (s1[i] && is_set(s1[i], set) == 1 && *s < str_len)
		--i;
	*e = i + 1;
	return (*e - *s);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	words_start;
	size_t	words_end;
	size_t	res_len;

	res_len = 0;
	words_start = 0;
	words_end = 0;
	if (!s1 || !set || (!s1 && !set))
		return (NULL);
	if (ft_strlen(s1) > 1)
		res_len = words_len(s1, set, &words_start, &words_end);
	res = malloc(sizeof(char) * (res_len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (words_start + i < words_end)
	{
		res[i] = s1[words_start + i];
		++i;
	}
	res[i] = '\0';
	return (res);
}
