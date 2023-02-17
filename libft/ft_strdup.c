/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:13:22 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/14 14:49:51 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	int		len;
	int		i;
	char	*res;

	if (!s)
		exit(EXIT_FAILURE);
	len = -1;
	i = -1;
	while (s[++len])
		;
	res = ft_malloc(sizeof(char) * (len + 1));
	while (s[++i])
	{
		res[i] = s[i];
	}
	res[i] = '\0';
	return (res);
}
