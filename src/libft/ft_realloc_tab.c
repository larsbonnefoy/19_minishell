/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:22:06 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/03 12:54:36 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_tab_memcpy(void *dst, const void *src, size_t n)
{
	char	**cpy;
	char	**temp_src;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	cpy = (char **)dst;
	temp_src = (char **)src;
	i = -1;
	while (++i < n)
		cpy[i] = temp_src[i];
	return (dst);
}

void	**ft_realloc_tab(void **p, size_t size_of, size_t size)
{
	void	*res;

	res = ft_malloc(size_of * (size + 1));
	if (!p)
		return (res);
	ft_bzero(res, size_of * (size + 1));
	ft_tab_memcpy(res, p, size);
	free(p);
	return (res);
}
