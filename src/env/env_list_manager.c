/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:08:48 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/14 23:13:34 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/env.h"

t_env	**env_init(void)
{
	t_env	**res;

	res = ft_malloc(sizeof(t_env *));
	res[0] = NULL;
	return (res);
}

t_env	*env_new(char *name, char *new_value, int export_value)
{
	t_env	*res;

	if (!name)
		exit(EXIT_FAILURE);
	res = ft_malloc(sizeof(t_env));
	res->value = new_value;
	res->name = name;
	res->export = export_value;
	res->next = NULL;
	return (res);
}

void	env_addfront(t_env *new_node, t_env **list)
{
	if (!new_node || !list)
		exit(EXIT_FAILURE);
	new_node->next = *list;
	*list = new_node;
}

void	env_free_node(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

void	env_free_all_node(t_env **list)
{
	t_env	*next;

	if (!list)
		exit(EXIT_FAILURE);
	while (*list)
	{
		next = (*list)->next;
		env_free_node(*list);
		*list = next;
	}
	free(list);
}
