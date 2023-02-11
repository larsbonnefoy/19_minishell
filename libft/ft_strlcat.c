/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:51:51 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/12 13:30:54 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	desti;
	size_t	srci;
	size_t	srclen;

	if (!dst && dstsize == 0)
		return (0);
	srci = 0;
	srclen = ft_strlen(src);
	desti = ft_strlen(dst);
	if (dstsize == 0 || (dstsize < desti))
		return (srclen + dstsize);
	while (src[srci] != '\0' && desti + srci < dstsize - 1)
	{
		dst[desti + srci] = src[srci];
		srci++;
	}
	dst[desti + srci] = '\0';
	return (desti + srclen);
}
