/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:37:38 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/12 13:32:14 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wrd_cnt(const char *s, char c);
static char	*ft_add_s(const char *s, int pos, int new_s);
static int	ft_fill_tab(char **tab, int size_tab, const char *s, char c);
static int	ft_free_all(char **tab, int i);

char	**ft_split(const char *s, char c)
{
	int		size_tab;
	char	**tab;
	int		check_return;	

	if (s == NULL)
		return (NULL);
	size_tab = ft_wrd_cnt(s, c);
	tab = malloc((size_tab + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	check_return = ft_fill_tab(tab, size_tab, s, c);
	if (check_return == -1)
		return (NULL);
	return (tab);
}

static int	ft_wrd_cnt(const char *s, char c)
{
	int	ft_wrd_cnt;
	int	a;

	a = 0;
	ft_wrd_cnt = 0;
	while (s[a] != '\0')
	{
		while (s[a] == c)
			a++;
		if (s[a] != c && (s[a] != '\0'))
			ft_wrd_cnt++;
		while ((s[a] != c) && (s[a] != '\0'))
			a++;
	}
	return (ft_wrd_cnt);
}

static char	*ft_add_s(const char *s, int pos, int new_s)
{
	int		i;
	int		j;
	char	*s_to_add;

	i = pos - new_s;
	s_to_add = malloc((new_s + 1) * sizeof(char));
	if (s_to_add == NULL)
		return (NULL);
	j = 0;
	while (j < new_s)
	{
		s_to_add[j] = (char)s[i];
		i++;
		j++;
	}
	s_to_add[j] = '\0';
	return (s_to_add);
}

static int	ft_fill_tab(char **tab, int size_tab, const char *s, char c)
{
	int	pos;
	int	max;
	int	new_s;

	pos = 0;
	max = size_tab;
	size_tab = -1;
	while (++size_tab < max)
	{
		new_s = 0;
		while (s[pos] == c)
			pos++;
		while (s[pos] != c && s[pos] != '\0')
		{
			new_s++;
			pos++;
		}
		tab[size_tab] = ft_add_s(s, pos, new_s);
		if (tab[size_tab] == NULL)
			return (ft_free_all(tab, size_tab));
	}
	tab[size_tab] = 0;
	return (0);
}

static	int	ft_free_all(char **tab, int i)
{
	int	j;

	j = 0;
	while (i <= j)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
	return (-1);
}
