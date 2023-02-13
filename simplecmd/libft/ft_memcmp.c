/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:20:20 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 10:02:45 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = -1;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (++i < n)
	{
		if (str2[i] != str1[i])
			return (str1[i] - str2[i]);
	}
	return (0);
}
