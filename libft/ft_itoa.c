/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:20:56 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/10 10:17:45 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include<stdio.h>

static int	ft_count(unsigned int nb);
static int	ft_check_neg(int n);

char	*ft_itoa(int n)
{
	char			*s;
	int				digits;
	int				neg;
	unsigned int	nb;

	nb = n;
	neg = ft_check_neg(n);
	if (neg == 1)
		nb = -n;
	digits = ft_count(nb);
	s = malloc(sizeof(char) * (digits + neg + 1));
	if (s == NULL)
		return (NULL);
	if (neg == 1)
		s[0] = '-';
	s[digits + neg] = '\0';
	while (digits > 0)
	{
		s[digits + neg - 1] = (nb % 10) + '0';
		nb = nb / 10;
		digits--;
	}
	return (s);
}

static int	ft_check_neg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static int	ft_count(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}
