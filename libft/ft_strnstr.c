/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:56:08 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/17 14:06:04 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	int		len_little;
	char	*res;

	i = -1;
	len_little = -1;
	res = (char *)big;
	while (little[++len_little])
		;
	if (len_little == 0)
		return (res);
	if (len == 0)
		return (NULL);
	while (big[++i] && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && j + i < len)
		{
			j++;
			if (j == len_little)
				return (&res[i]);
		}
	}
	return (NULL);
}
