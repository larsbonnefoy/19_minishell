/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:50:39 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/01 11:55:55 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_export.h"

int	is_export(char *str)
{
	int	i;

	i = -1;
	if (!str)
		exit(EXIT_FAILURE);
	while (str[++i])
	{
		if ((str[i] == 32) || (str[i] <= 13 && str[i] >= 9))
			return (0);
		if (str[i] == '=')
			break ;
	}
	if (!str[i] || ft_isdigit(str[0]))
		return (0);
	if (!str[++i])
		return (0);
	return (1);
}

int	export_error(char *str)
{

}

int	ft_export(char **av, t_env **l_env, char **env)
{
	int		i;
	char	*name;
	char	*val;
	t_env	*new;
	int		ret_val;

	i = -1;
	if (!av)
		exit(EXIT_FAILURE);
	while (av[++i])
	{
		if (is_export(av[i]))
		{
			name = getname(av[i]);
			val = getval(av[i]);
			new = env_new(name, val, TRUE);
			env_reassign(new, l_env);
		}
		else
			export_error(av[i]);
	}
	return (ret_val);
}
