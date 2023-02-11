/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:29:05 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/12 14:35:51 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_check_set(char c, char const *set);
static size_t	ft_get_trim_beg(char const *s1, char const *set);
static size_t	ft_get_trim_end(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	trim_beg;
	size_t	trim_end;
	size_t	a;
	char	*ret;
	size_t	size_ret;

	if (s1 == NULL || set == NULL)
		return (NULL);
	trim_beg = ft_get_trim_beg(s1, set);
	trim_end = ft_get_trim_end(s1, set);
	if (((int)ft_strlen(s1) - (int)trim_beg - (int)trim_end) < 0)
		size_ret = 0;
	else
		size_ret = ft_strlen(s1) - trim_end - trim_beg;
	ret = malloc(sizeof(char) * (size_ret + 1));
	if (ret == NULL)
		return (NULL);
	ret[size_ret] = '\0';
	a = 0;
	while (a < size_ret)
	{	
		ret[a] = (char)s1[trim_beg + a];
		a++;
	}
	return (ret);
}

static int	ft_check_set(char c, char const *set)
{
	size_t	a;

	a = 0;
	while (set[a] != '\0')
	{
		if (c == set[a])
			return (1);
		a++;
	}
	return (0);
}

static size_t	ft_get_trim_beg(char const *s1, char const *set)
{
	size_t	trim_beg;
	size_t	a;

	a = 0;
	trim_beg = 0;
	while (ft_check_set(s1[a], set) == 1)
	{	
		trim_beg++;
		a++;
	}
	return (trim_beg);
}

static size_t	ft_get_trim_end(char const *s1, char const *set)
{
	size_t	trim_end;
	size_t	a;

	trim_end = 0;
	a = ft_strlen(s1) - 1;
	if ((long long int)ft_strlen(s1) - 1 < 0)
		a = 0;
	while (ft_check_set(s1[a], set) == 1 && a > 0)
	{
		trim_end++;
		a--;
	}
	return (trim_end);
}
