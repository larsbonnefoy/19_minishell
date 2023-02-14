/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env_list_manager.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:48 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/14 18:36:32 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_env.h"
//TODO SUPPORT FOR REASSIGNING
t_local	**local_env_init(void)
{
	t_local	**res;

	res = ft_malloc(sizeof(t_local *));
	res[0] = NULL;
	return (res);
}

t_local	*local_new(char *name, char *new_value)
{
	t_local	*res;

	if (!new_value)
		exit(EXIT_FAILURE);
	res = ft_malloc(sizeof(t_local));
	res->value = new_value;
	res->name = name;
	res->next = NULL;
	return (res);
}

void	local_addfront(t_local *new_node, t_local **list)
{
	if (!new_node || !list)
		exit(EXIT_FAILURE);
	new_node->next = *list;
	*list = new_node;
}

void	local_free_node(t_local *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

void	local_free_all_node(t_local **list)
{
	t_local	*next;

	if (!list)
		exit(EXIT_FAILURE);
	while (*list)
	{
		next = (*list)->next;
		local_free_node(*list);
		*list = next;
	}
	free(list);
}

