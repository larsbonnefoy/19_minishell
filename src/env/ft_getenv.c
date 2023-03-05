/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:04:37 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/17 08:48:30 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/env.h"

/*
* Return the value associated to var_name in the local environement
* if var_name does not exist in the local env the function returns NULL
*/
char	*ft_getenv(char *var_name, t_env **l_env)
{
	t_env	*head;
	char	*value;
	int		len_var_name;

	if (!l_env || !var_name)
		exit(EXIT_FAILURE);
	head = *l_env;
	len_var_name = ft_strlen(var_name);
	while (*l_env)
	{
		if (ft_strncmp((*l_env)->name, var_name, len_var_name) == 0)
		{
			value = (*l_env)->value;
			*l_env = head;
			return (value);
		}
		*l_env = (*l_env)->next;
	}
	*l_env = head;
	return (NULL);
}
