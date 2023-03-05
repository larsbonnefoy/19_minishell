/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:15:11 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 09:54:50 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	size_t			len_str;
	unsigned char	chr;
	unsigned char	*str;

	i = -1;
	len_str = -1;
	chr = (unsigned char)c;
	str = (unsigned char *)s;
	while (str[++len_str] != '\0')
		;
	while (++i < n)
		if (chr == str[i])
			return (&str[i]);
	return (NULL);
}
