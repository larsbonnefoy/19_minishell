/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:49:08 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/06 14:57:36 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*str;
	int		a;

	len = 0;
	len = ft_strlen(s1);
	str = malloc((len +1) * sizeof(char));
	if (str == NULL)
		return (0);
	a = 0;
	while (s1[a] != '\0')
	{
		str[a] = s1[a];
		a++;
	}
	str[a] = '\0';
	return (str);
}
