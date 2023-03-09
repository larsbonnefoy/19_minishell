/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 09:04:24 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/09 11:47:45 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			++i;
		if (s[i] != c && s[i])
			++res;
		while (s[i] != c && s[i])
			++i;
	}
	return (res);
}

static char	**free_all(char **tab, size_t nbr_words)
{
	size_t	i;

	i = -1;
	while (++i < nbr_words)
		free(tab[i]);
	free(tab);
	return (NULL);
}

static size_t	word_pos(size_t *start, size_t prev_end, char const *s, char c)
{
	while (s[prev_end] == c && s[prev_end])
			++prev_end;
	*start = prev_end;
	while (s[prev_end] != c && s[prev_end])
		++prev_end;
	return (prev_end);
}

static char	**put_word(char const *s, char c, char **res, size_t nbr_words)
{
	size_t	start;
	size_t	end;
	size_t	i;
	size_t	j;
	size_t	k;

	i = -1;
	end = 0;
	start = 0;
	while (++i < nbr_words)
	{
		j = end;
		end = word_pos(&start, j, s, c);
		res[i] = ft_malloc(sizeof(char) * ((end - start) + 1));
		if (!res[i])
			return (free_all(res, i));
		res[i][end - start] = '\0';
		j = start;
		k = 0;
		while (j < end)
			res[i][k++] = s[j++];
	}
	return (res);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	size_t	nbr_words;

	if (!s)
		exit(EXIT_FAILURE);
	nbr_words = word_count(s, c);
	res = ft_malloc(sizeof(char *) * (nbr_words + 1));
	res[nbr_words] = NULL;
	res = put_word(s, c, res, nbr_words);
	return (res);
}
