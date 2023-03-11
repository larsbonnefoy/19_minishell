/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_local.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:03:46 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/10 23:14:58 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/ft_export.h"

int	is_local(char *str)
{
	int	i;

	i = -1;
	if (!str)
		exit(EXIT_FAILURE);
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if ((str[i] == 32) || (str[i] <= 13 && str[i] >= 9)
			|| !ft_isalnum(str[i]))
			return (0);
	}
	if (!ft_isalpha(str[0]) || str[i] != '=')
		return (0);
	return (1);
}

char	**make_local(char **av)
{
	char	**res;
	int		i;

	if (!av)
		exit(EXIT_FAILURE);
	if (**av == '\0')
		return (av);
	res = ft_malloc(sizeof(char *) * 2);
	res[0] = ft_strdup("ft_local");
	res[1] = NULL;
	i = -1;
	while (av[++i])
	{
		if (is_local(av[i]) >= 0)
		{
			res = (char **)ft_realloc_tab((void **)res, sizeof(char *), i + 2);
			res[i + 1] = ft_strdup(av[i]);
			res[i + 2] = NULL;
		}
		else
		{
			free_char_tab(res);
			res = ft_tabdup(&av[i]);
			free_char_tab(av);
			return (res);
		}
	}
	free_char_tab(av);
	return (res);
}

int	ft_local(char **av, char ***env, t_env **l_env)
{
	int	ret_val;

	if (!av)
		exit(EXIT_FAILURE);
	if (!av[1])
		return (0);
	ret_val = 0;
	ret_val = add_exports_to_list(av, l_env, FALSE);
	free_char_tab(*env);
	*env = list_to_env(l_env);
	return (ret_val);
}
