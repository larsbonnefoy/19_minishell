/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:16:35 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 10:02:53 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*cpy;
	char	*temp_src;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	cpy = (char *)dst;
	temp_src = (char *)src;
	i = -1;
	while (++i < n)
		cpy[i] = temp_src[i];
	return (dst);
}
