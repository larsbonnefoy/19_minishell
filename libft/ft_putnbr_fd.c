/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:59:44 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/10 10:24:59 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	unb;

	unb = nb;
	if (nb < 0)
	{
		write(fd, "-", 1);
		unb = -nb;
	}
	if (unb < 10)
	{
		unb += '0';
		write(fd, &(unb), 1);
	}
	else
	{
		ft_putnbr_fd(unb / 10, fd);
		ft_putnbr_fd(unb % 10, fd);
	}
}
