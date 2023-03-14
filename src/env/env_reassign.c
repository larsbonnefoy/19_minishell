/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_reassign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:36:25 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/15 00:16:50 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/env.h"
#include "../../Includes/global.h"

static void	assign(t_env *to_add, t_env **l_env)
{
	char	*tmp;

	if (to_add->export)
		(*l_env)->export = to_add->export;
	if (to_add->value)
	{
		tmp = (*l_env)->value;
		(*l_env)->value = to_add->value;
		to_add->value = tmp;
		env_free_node(to_add);
	}	
}

static void	join(t_env *to_add, t_env **l_env)
{
	char	*tmp;

	if (to_add->export)
		(*l_env)->export = to_add->export;
	if (to_add->value)
	{
		tmp = (*l_env)->value;
		(*l_env)->value = ft_strjoinf(tmp, to_add->value);
		env_free_node(to_add);
	}
}

void	env_reassign(t_env *to_add, t_env **l_env)
{
	t_env	*head;
	int		len;

	if (!to_add || !l_env)
		exit(EXIT_FAILURE);
	head = *l_env;
	len = ft_strlen(to_add->name);
	while (*l_env)
	{
		if (ft_strncmp((*l_env)->name, to_add->name, len) == 0)
		{
			assign(to_add, l_env);
			*l_env = head;
			return ;
		}
		*l_env = (*l_env)->next;
	}
	*l_env = head;
	env_addfront(to_add, l_env);
}

void	reassign_global(t_env **l_env)
{
	t_env	*head;
	int		len;
	t_env	*to_add;

	if (!l_env)
		exit(EXIT_FAILURE);
	head = *l_env;
	len = ft_strlen("?");
	while (*l_env)
	{
		if (ft_strncmp((*l_env)->name, "?", len) == 0)
		{
			free((*l_env)->value);
			(*l_env)->value = ft_itoa(g_ret_val);
			*l_env = head;
			return ;
		}
		*l_env = (*l_env)->next;
	}
	*l_env = head;
	to_add = env_new(ft_strdup("?"), ft_itoa(g_ret_val), 0);
	env_addfront(to_add, l_env);
}

void	env_join(t_env *to_add, t_env **l_env)
{
	t_env	*head;
	int		len;

	if (!to_add || !l_env)
		exit(EXIT_FAILURE);
	head = *l_env;
	len = ft_strlen(to_add->name);
	while (*l_env)
	{
		if (ft_strncmp((*l_env)->name, to_add->name, len) == 0)
		{
			join(to_add, l_env);
			*l_env = head;
			return ;
		}
		*l_env = (*l_env)->next;
	}
	*l_env = head;
	env_addfront(to_add, l_env);
}
