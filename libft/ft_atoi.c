/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:59:26 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/17 14:04:00 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	if ((c == 32) || (c <= 13 && c >= 9))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	long int		res;
	long int		tmp;
	int				sign;

	res = 0;
	tmp = 0;
	sign = 1;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == 45 || *nptr == 43)
		if (*(nptr++) == 45)
			sign *= -1;
	while (*nptr >= 48 && *nptr <= 57)
	{
		res = (10 * res + (*nptr - 48));
		if (res < tmp && sign == 1)
			return (-1);
		if (res < tmp && sign == -1)
			return (0);
		tmp = res;
		nptr++;
	}
	return ((int)(res * sign));
}
