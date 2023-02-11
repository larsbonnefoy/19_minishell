/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:10:19 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/11 13:53:39 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	subs = malloc((len + 1) * sizeof(char));
	if (subs == NULL)
		return (NULL);
	i = 0;
	while (i < len && s)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
