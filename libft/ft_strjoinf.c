/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:19:34 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/11/28 09:13:54 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinf(const char *s1, const char *s2)
{
	int		size;
	int		a;
	int		b;
	char	*str;

	a = -1;
	b = -1;
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
	{	
		free((char *)s1);
		return (NULL);
	}
	while (s1[++a] != '\0')
		str[a] = (char)s1[a];
	free((char *)s1);
	while (s2[++b] != '\0')
		str[a + b] = (char)s2[b];
	str[a + b] = '\0';
	return (str);
}
