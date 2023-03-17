/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:23:08 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/17 14:31:09 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/ft_unset.h"

int	is_in_lenv(char *name, t_env **l_env, t_env **head, t_env **last)
{
	if (ft_strncmp(name, (*l_env)->name, ft_strlen(name)) == 0)
	{
		if (*l_env != *head)
			(*last)->next = (*l_env)->next;
		else
			*head = (*l_env)->next;
		env_free_node(*l_env);
		return (1);
	}
	return (0);
}

int	ft_unset(char **av, char ***env, t_env **l_env)
{
	int		i;
	t_env	*last;
	t_env	*head;

	if (!av || !av[0] || !l_env || !*l_env || !env)
		exit(EXIT_FAILURE);
	if (!av[1])
		return (0);
	head = *l_env;
	i = 0;
	while (av[++i])
	{
		*l_env = head;
		while (*l_env)
		{
			if (is_in_lenv(av[i], l_env, &head, &last))
				break ;
			last = *l_env;
			*l_env = (*l_env)->next;
		}
	}
	*l_env = head;
	free_char_tab(*env);
	*env = list_to_env(l_env);
	return (0);
}
