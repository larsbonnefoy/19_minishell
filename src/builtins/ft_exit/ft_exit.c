/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:51:34 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/05 19:27:43 by hdelmas          ###   ########.fr       */
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

int	ft_exit(char **av)
{
	long int	x;
	int			over;

	if (!av)
		exit(EXIT_FAILURE);
	ft_putendl_fd("exit", 1);
	if (!av[1])
		exit(EXIT_SUCCESS);
	over = 0;
	x = ft_atol(av[1], &over);
	if (over)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	if (!av[2])
		exit(x);
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	return (0);
}
