/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:27:59 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/14 23:15:01 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/ft_echo.h"

static int	has_option(char **av)
{
	int	i;
	int	j;

	i = 0;
	if (!av)
		return (0);
	while (av[++i])
	{
		j = 0;
		if (av[i][j] != '-')
			return (i);
		while (av[i][++j])
			if (av[i][j] != 'n')
				return (i);
	}
	return (i);
}

int	ft_echo(char **av, char ***env, t_env **l_env)
{
	int	option;
	int	i;
	int	nbr_av;
	int	ac;

	(void)l_env;
	(void)env;
	option = has_option(av);
	ac = 0;
	while (av[++ac])
		;
	i = option - 1;
	while (av[++i])
	{
		write(1, av[i], ft_strlen(av[i]));
		if (i != ac - 1)
			write(1, " ", 1);
	}
	if (option == 1)
		write(1, "\n", 1);
	return (0);
}
