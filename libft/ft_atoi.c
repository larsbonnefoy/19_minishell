/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:06:30 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/12 14:16:14 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_create_out(int i, int sign, const char *str);

int	ft_atoi(const char *str)
{
	int	sign;
	int	base;
	int	i;

	i = 0;
	base = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{	
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (ft_isdigit(str[i]) == 1)
	{	
		base = ft_create_out(i, sign, str);
		return (base * sign);
	}		
	else
		return (0);
}

static int	ft_create_out(int i, int sign, const char *str)
{
	unsigned long int	out;

	out = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		out = (out * 10) + (str[i] - 48);
		if (out > (unsigned)LONG_MAX && sign == -1)
			return (0);
		else if (out > (unsigned)LONG_MAX && sign == 1)
			return (-1);
		i++;
	}
	return ((int)out);
}
