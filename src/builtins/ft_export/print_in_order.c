/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_in_order.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:59:19 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/17 15:28:04 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/ft_export.h"

static char	*quad_join(char *first, char *second, char *third, char *last)
{
	char	*fise;
	char	*fisethi;
	char	*fisethila;

	fise = ft_strjoin(first, second);
	fisethi = ft_strjoin(fise, third);
	free(fise);
	fisethila = ft_strjoin(fisethi, last);
	free(fisethi);
	return (fisethila);
}

static char	**list_to_print(t_env **l_env)
{
	t_env	*head;
	int		s;
	char	**res;

	s = 0;
	head = *l_env;
	res = ft_calloc_exit(sizeof(char *), (s + 1));
	while (*l_env)
	{
		if ((*l_env)->export && (*l_env)->value)
		{
			res = (char **)ft_realloc_tab((void **)res, sizeof(char *), (++s));
			res[s - 1] = quad_join((*l_env)->name,
					"=\"", (*l_env)->value, "\"");
		}
		else if ((*l_env)->export && !(*l_env)->value)
		{
			res = (char **)ft_realloc_tab((void **)res, sizeof(char *),
					(++s));
			res[s - 1] = ft_strdup((*l_env)->name);
		}
		*l_env = (*l_env)->next;
	}
	*l_env = head;
	return (res);
}

static int	*create_order(char **env, int size)
{
	int		*array;
	char	*last_name;
	char	*name;
	int		i;
	int		j;

	array = ft_calloc_exit(size, sizeof(int));
	i = -1;
	while (env[++i])
	{
		j = -1;
		last_name = getname(env[i]);
		while (env[++j])
		{
			name = getname(env[j]);
			if ((ft_strncmp(last_name,
						name, ft_strlen(name) + 1)) > 0)
				array[i] += 1;
			free(name);
		}
		free(last_name);
	}
	return (array);
}

int	print_in_order(t_env **l_env)
{
	int		size;
	int		*array;
	int		i;
	int		j;
	char	**env;

	if (!l_env)
		exit(EXIT_FAILURE);
	env = list_to_print(l_env);
	size = -1;
	while (env[++size])
		;
	array = create_order(env, size);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (j < size && i != array[++j])
			;
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env[j], 1);
	}
	free_char_tab(env);
	free(array);
	return (0);
}
