/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:13:22 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/13 08:45:18 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	int		len;
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	len = -1;
	i = -1;
	while (s[++len])
		;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	while (s[++i])
	{
		res[i] = s[i];
	}
	res[i] = '\0';
	return (res);
}
