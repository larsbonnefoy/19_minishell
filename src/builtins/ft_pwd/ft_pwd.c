/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:56:22 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/06 15:24:36 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/ft_pwd.h"

int	ft_pwd(char **av, char ***env, t_env **l_env)
{
	char	buf[1024];

	(void)env;
	(void)l_env;
	if (getcwd(buf, 1024))
	{
		ft_putendl_fd(buf, 1);
		return (0);
	}
	perror("pwd");
	return (1);
}

// int	main(int ac,  char **av, char **env)
// {
// 	ft_pwd(av);
// }
