/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:50:39 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/01 16:42:03 by hdelmas          ###   ########.fr       */
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
		if ((str[i] == 32) || (str[i] <= 13 && str[i] >= 9)
			|| !ft_isalnum(str[i]))
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

static int	export_error(char *str)
{
	if (!str)
		exit(EXIT_FAILURE);
	ft_putendl_fd("minishell: export: `", 2);
	ft_putendl_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

static int	add_exports_to_list(char **av, t_env **l_env)
{
	int		ret_val;
	int		i;
	char	*name;
	t_env	*new;
	char	*val;

	ret_val = 0;
	i = 1;
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
			ret_val = export_error(av[i]);
	}
	return (ret_val);
}

static int	print_in_order(char **env)
{
	int		i;
	char	**tmp;

	i = -1;
	if (!env)
		exit(EXIT_FAILURE);
	while (env[++i])
		;
	tmp = ft_malloc(sizeof(char *) * (i + 1));
	//
	return (0);
}

int	ft_export(char **av, t_env **l_env, char **env)
{
	
	int	ret_val;

	ret_val = 0;
	if (!av)
		exit(EXIT_FAILURE);
	if (!av[1])
		return (print_in_order(env));
	ret_val = add_exports_to_list(av, l_env);
	// free_env(env);
	env = list_to_env(l_env);
	return (ret_val);
}

char	**ft_tabdup_free(char **s)
{
	int		len;
	int		i;
	char	**res;

	if (!s)
		exit(EXIT_FAILURE);
	len = -1;
	i = -1;
	while (s[++len])
		;
	res = ft_malloc(sizeof(char *) * (len + 1));
	while (s[++i])
		res[i] = s[i];
	res[i] = NULL;
	return (res);
}

int main(int ac, char **av, char **env)
{
	t_env	**l_env;

	l_env = env_to_list(env);
	env = ft_tabdup_free(env);
	ft_env(&"boop", env);
	ft_export(av, l_env, env);
	ft_env(&"boop", env);
	return (0);
}
