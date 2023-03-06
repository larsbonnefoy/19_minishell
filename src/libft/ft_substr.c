/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:54:57 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/17 11:02:05 by lbonnefo         ###   ########.fr       */
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
	res = ft_malloc(sizeof(char) * (len_to_check + 1));
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
