/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:54:57 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 10:01:09 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	len_to_check;

	i = 0;
	len_to_check = 0;
	if (!s)
		return (NULL);
	while (start < ft_strlen(s)
		&& s[start + len_to_check] && len_to_check < len)
		len_to_check++;
	res = malloc(sizeof(char) * (len_to_check + 1));
	if (!res)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (s[start + i] && i < len_to_check)
		{
			res[i] = s[start + i];
			i++;
		}
	}
	res[i] = '\0';
	return (res);
}
