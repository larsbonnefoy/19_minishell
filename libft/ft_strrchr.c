/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:32:08 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 10:00:04 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = -1;
	res = (char *)s;
	while (s[++i])
		;
	if ((char)c == s[i])
		return (&res[i]);
	while (--i >= 0)
		if ((char)c == s[i])
			return (&res[i]);
	return (NULL);
}
