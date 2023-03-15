/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_atol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:47:33 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/14 23:15:13 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/ft_exit.h"

static void	issign(char **nptr, long int *sign)
{
	if (**nptr == 45 || **nptr == 43)
	{
		if (**nptr == 45)
			*sign *= -1;
		*nptr += 1;
	}
}

static void	while_isspace(char **nptr)
{
	while ((**nptr == 32) || (**nptr <= 13 && **nptr >= 9))
		(*nptr)++;
}

static int	is_over(size_t nbr, long int sign)
{
	if ((nbr > LONG_MAX && sign > 0) || (nbr > (size_t)(LONG_MIN) && sign < 0))
		return (1);
	return (0);
}

long int	ft_atol(char *nptr, int *over)
{
	size_t		res;
	long int	sign;

	res = 0;
	sign = 1;
	while_isspace(&nptr);
	issign(&nptr, &sign);
	if (!ft_isdigit(*nptr))
		*over = 1;
	while (*nptr)
	{
		if (is_over(res, sign) || !ft_isdigit(*nptr))
		{
			while_isspace(&nptr);
			if (*nptr || is_over(res, sign))
				*over = 1;
			return (res * sign);
		}
		res = (10 * res + (*nptr - 48));
		nptr++;
	}
	return ((long int)(res * sign));
}
