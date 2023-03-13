/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_local.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:03:46 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/08 08:20:10 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/ft_export.h"

int	ft_local(char **av, char ***env, t_env **l_env)
{
	int	ret_val;

	if (!av || !av[0] || av[1])
		exit(EXIT_FAILURE);
	ret_val = 0;
	ret_val = add_exports_to_list(av, l_env, FALSE);
	free_char_env(*env);
	*env = list_to_env(l_env);
	return (ret_val);
}
