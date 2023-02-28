/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:56:22 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/27 17:41:24 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd.h"

int	ft_pwd(char **av)
{
	char	buf[1024];

	if (av[1])
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		return (1);
	}
	if (getcwd(buf, 12))
	{
		ft_putendl_fd(buf, 1);
		return (0);
	}
	perror("pwd");
	return (1);
}
