/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:01:07 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/08 15:45:14 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/env.h"

char	*getname(char *str)
{
	int	i;

	i = -1;
	if (!str)
		exit(EXIT_FAILURE);
	while (str[++i] && (str[i] != '=' && str[i] != '+'))
		;
	return (ft_strldup(str, i));
}

char	*getval(char *str)
{
	int	i;

	i = -1;
	if (!str || !str[i])
		return (NULL);
	while (str[++i] && str[i] != '=')
		;
	if (!str[i])
		return (NULL);
	return (ft_strdup(&str[++i]));
}

t_env	**env_to_list(char **env)
{
	t_env	**list;
	int		i;
	char	*name;
	char	*value;
	t_env	*new;

	if (!env || !*env)
		exit(EXIT_FAILURE);
	i = -1;
	list = env_init();
	while (env[++i])
	{
		name = getname(env[i]);
		value = getval(env[i]);
		new = env_new(name, value, TRUE);
		env_addfront(new, list);
	}
	return (list);
}

char	**list_to_env(t_env **l_env)
{
	t_env	*head;
	int		size;
	char	**res;
	char	*tmp;

	size = 0;
	head = *l_env;
	res = ft_calloc_exit(sizeof(char *), (size + 1));
	while (*l_env)
	{
		if ((*l_env)->export && (*l_env)->value)
		{
			res = (char **)ft_realloc_tab((void **)res, sizeof(char *),
					(++size));
			tmp = ft_strjoin((*l_env)->name, "=");
			res[size - 1] = ft_strjoin(tmp, (*l_env)->value);
			free(tmp);
		}
		*l_env = (*l_env)->next;
	}
	*l_env = head;
	return (res);
}

void	free_char_env(char **env)
{
	size_t	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}
