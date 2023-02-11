/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:12:43 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/11 15:43:57 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	a;
	char			*str;
	int				len;

	if (s == NULL || f == NULL)
		return (0);
	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	a = 0;
	while (s[a] != '\0')
	{
		str[a] = f(a, ((char *)s)[a]);
		a++;
	}
	str[a] = '\0';
	return (str);
}
