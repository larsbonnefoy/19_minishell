/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:23:43 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 09:59:30 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	srclen;

	i = -1;
	srclen = -1;
	while (src[++srclen])
		;
	if (dstsize == 0)
		return (srclen);
	while (++i < dstsize - 1 && src[i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (srclen);
}
