/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_reassign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:36:25 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/05 19:28:17 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/env.h"
void	env_reassign(t_env *to_add, t_env **l_env)
{
	t_env	*head;
	char	*tmp;
	int		len;

	if (!to_add || !l_env)
		exit(EXIT_FAILURE);
	head = *l_env;
	len = ft_strlen(to_add->name);
	while (*l_env)
	{
		if (ft_strncmp((*l_env)->name, to_add->name, len) == 0)
		{
			if (to_add->export)
				(*l_env)->export = to_add->export;
			tmp = (*l_env)->value;
			(*l_env)->value = to_add->value;
			to_add->value = tmp;
			env_free_node(to_add);
			*l_env = head;
			return ;
		}
		*l_env = (*l_env)->next;
	}
	*l_env = head;
	env_addfront(to_add, l_env);
}
