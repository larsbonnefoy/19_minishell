/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:52:22 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 09:59:48 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	char	*res;
	size_t	i;

	if (!s || !f || (!s && !f))
		return (NULL);
	s_len = ft_strlen(s);
	res = malloc (sizeof(char) * (s_len + 1));
	if (!res)
		return (NULL);
	res[s_len] = '\0';
	i = -1;
	while (s[++i])
	{
		res[i] = f(i, s[i]);
	}
	return (res);
}
