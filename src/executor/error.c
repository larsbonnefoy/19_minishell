/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:56:45 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/08 16:03:31 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/executor.h"

void	ft_perror(char *cmd_name, char *msg)
{
	if (!cmd_name)
		return ;
	if (msg != NULL)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	else
		perror(cmd_name);
}
