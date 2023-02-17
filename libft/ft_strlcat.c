/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:49:39 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 09:59:18 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;

	i = -1;
	if ((!dst || !src) && dstsize == 0)
		return (0);
	dstlen = ft_strlen(dst);
	if (dstsize <= dstlen || !dst || !src)
		return (ft_strlen(src) + dstsize);
	while (++i + dstlen < dstsize - 1 && src[i])
		dst[dstlen + i] = src[i];
	dst[dstlen + i] = '\0';
	return (dstlen + ft_strlen(src));
}
