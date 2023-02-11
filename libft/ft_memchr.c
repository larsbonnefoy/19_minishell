/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:01:52 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/11 15:49:47 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			a;
	unsigned char	*str;

	a = 0;
	str = (unsigned char *)s;
	while (a < n)
	{
		if (str[a] == (unsigned char)c)
			return (&str[a]);
		a++;
	}
	return (NULL);
}
