/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_local_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:04:37 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/17 08:48:30 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_env.h"

/*
* Return the value associated to var_name in the local environement
* if var_name does not exist in the local env the function returns NULL
*/
char	*ft_get_local_env(char *var_name, t_local **local)
{
	t_local	*head;
	char	*value;
	int		len_var_name;

	if (!local || !var_name)
		exit(EXIT_FAILURE);
	head = *local;
	len_var_name = ft_strlen(var_name);
	while (*local)
	{
		if (ft_strncmp((*local)->name, var_name, len_var_name) == 0)
		{
			value = (*local)->value;
			*local = head;
			return (value);
		}
		*local = (*local)->next;
	}
	*local = head;
	return (NULL);
}
