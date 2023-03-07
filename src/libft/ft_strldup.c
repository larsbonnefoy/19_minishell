/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:30:08 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/15 16:58:17 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 * strdup but either stop at the EOS or at max_len
 */
char	*ft_strldup(char *s, int max_len)
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
	if (len > max_len)
		len = max_len;
	res = ft_malloc(sizeof(char) * (len) + 1);
	while (s[++i] && i < len)
	{
		res[i] = s[i];
	}
	res[i] = '\0';
	return (res);
}
