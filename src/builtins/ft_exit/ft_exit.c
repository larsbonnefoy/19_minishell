/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:51:34 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/06 16:57:30 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/ft_exit.h"

static void	print_err(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	exit(2);
}

int	ft_exit(char **av, char ***env, t_env **l_env)
{
	long int	x;
	int			over;

	(void)l_env;
	(void)env;
	if (!av)
		exit(EXIT_FAILURE);
	ft_putendl_fd("exit", 1);
	if (!av[1])
		exit(EXIT_SUCCESS);
	over = 0;
	x = ft_atol(av[1], &over);
	if (over)
		print_err(av[1]);
	if (!av[2])
		exit(x);
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	return (0);
}
