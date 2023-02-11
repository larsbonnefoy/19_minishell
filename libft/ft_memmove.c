/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:52:10 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/06 12:12:06 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	a;

	if (dst == 0 && src == 0)
		return (NULL);
	if (src < dst)
	{
		a = len;
		while (0 < a)
		{
			a--;
			((unsigned char *)dst)[a] = ((unsigned char *)src)[a];
		}
	}
	else
	{
		a = 0;
		while (a < len)
		{
			((unsigned char *)dst)[a] = ((unsigned char *)src)[a];
			a++;
		}
	}
	return (dst);
}
