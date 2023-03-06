/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:13:19 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 09:51:50 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	to_ascii(char *res, size_t nbr, size_t res_size, int sign)
{
	res_size--;
	while (nbr > 9)
	{
		res[res_size--] = (nbr % 10) + 48;
		nbr /= 10;
	}
	res[res_size] = nbr + 48;
	if (sign == -1)
		res[0] = 45;
}

char	*ft_itoa(int n)
{
	int		sign;
	size_t	nbr;
	char	*res;
	size_t	res_size;

	sign = 1;
	res_size = 1;
	if (n < 0)
	{
		sign = -1;
		res_size = 2;
	}
	nbr = ((long int)n * sign);
	while (nbr > 9)
	{
		nbr /= 10;
		res_size++;
	}
	nbr = ((long int)n * sign);
	res = malloc(sizeof(char) * (res_size + 1));
	if (!res)
		return (NULL);
	res[res_size] = '\0';
	to_ascii(res, nbr, res_size, sign);
	return (res);
}
