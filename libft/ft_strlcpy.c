/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:39:46 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/06 08:55:59 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	srclen;

	a = 0;
	srclen = 0;
	while (src[srclen] != '\0')
		srclen++;
	if (dstsize == 0)
		return (srclen);
	while (src[a] != '\0' && a < dstsize -1)
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (srclen);
}
