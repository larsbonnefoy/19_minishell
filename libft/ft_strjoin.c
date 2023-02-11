/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:28:34 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/12 13:31:08 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	int		a;
	int		b;
	char	*str;

	if (!s1 || !s2)
		return (0);
	a = 0;
	b = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	while (s1[a] != '\0')
	{
		str[a] = (char)s1[a];
		a++;
	}
	while (s2[b] != '\0')
	{
		str[a + b] = (char)s2[b];
		b++;
	}
	str[a + b] = '\0';
	return (str);
}
