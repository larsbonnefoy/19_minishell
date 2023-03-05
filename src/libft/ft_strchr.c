/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:06:25 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 09:58:40 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = -1;
	res = (char *)s;
	while (s[++i])
		if ((char)c == s[i])
			return ((char *)&res[i]);
	if ((char)c == s[i])
		return ((char *)&res[i]);
	return (NULL);
}
