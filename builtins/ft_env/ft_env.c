/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:14:45 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/02 14:33:17 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_env.h"

int	ft_env(char **av, char **env)
{
	int	i;

	i = -1;
	if (av[1])
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (1);
	}
	if (!env)
	{
		ft_putendl_fd("env: no env", 2);
		return (1);
	}
	while (env[++i])
		ft_putendl_fd(env[i], 1);
	return (0);
}
