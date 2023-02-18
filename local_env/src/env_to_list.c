/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:01:07 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/17 15:40:45 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static char	*getname(char *str)
{
	int	i;

	i = -1;
	if (!str)
		exit(EXIT_FAILURE);
	while (str[++i] && str[i] != '=')
		;
	return (ft_strldup(str, i));
}

static char	*getval(char *str)
{
	int	i;

	i = -1;
	if (!str)
		exit(EXIT_FAILURE);
	while (str[++i] && str[i] != '=')
		;
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
