/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:21:04 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/11 16:27:26 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (!haystack && len == 0)
		return (0);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[a] != '\0' && a < len)
	{
		b = 0;
		if (haystack[a] == needle[b])
		{
			while ((haystack[a + b] == needle[b] && a + b < len))
			{	
				b++;
				if (needle[b] == '\0')
					return ((char *)&haystack[a]);
			}
		}
		a++;
	}
	return (NULL);
}
//segfault quand haystack = NULL && len = 0 (og return null) 
//og segfault si needle = NULL || si haystack = NULL && len !0
