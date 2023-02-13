/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:32:35 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 10:02:51 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cpy;
	char	*temp_src;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (len == 0)
		return (dst);
	cpy = (char *)dst;
	temp_src = (char *)src;
	if (temp_src < cpy)
	{
		i = len;
		while (--i > 0)
			cpy[i] = temp_src[i];
		cpy[i] = temp_src[i];
	}
	else
	{
		i = -1;
		while (++i < len)
			cpy[i] = temp_src[i];
	}
	return (dst);
}
