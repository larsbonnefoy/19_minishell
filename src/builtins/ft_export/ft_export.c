/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:50:39 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/08 16:44:37 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/ft_export.h"

int	is_export(char *str)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	if (!str)
		exit(EXIT_FAILURE);
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+' && str[i + 1] == '=')
		{
			check = 1;
			break ;
		}
		if ((str[i] == 32) || (str[i] <= 13 && str[i] >= 9)
			|| !ft_isalnum(str[i]))
			return (-1);
	}
	if (!ft_isalpha(str[0]))
		return (-1);
	return (check);
}

static int	export_error(char *str)
{
	if (!str)
		exit(EXIT_FAILURE);
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

int	add_exports_to_list(char **av, t_env **l_env, int export)
{
	int		ret_val;
	int		i;
	t_env	*new;
	int		check;
	void	(*assign[2])(t_env *to_add, t_env **l_env);

	ret_val = 0;
	i = export - 1;
	assign[0] = &env_reassign;
	assign[1] = &env_join;
	while (av[++i])
	{
		check = is_export(av[i]);
		if (check >= 0)
		{
			printf("check>[%d]\n", check);
			new = env_new(getname(av[i]), getval(av[i]), export);
			assign[check](new, l_env);
		}
		else
			ret_val = export_error(av[i]);
	}
	return (ret_val);
}

int	ft_export(char **av, char ***env, t_env **l_env)
{
	int	ret_val;

	ret_val = 0;
	if (!av)
		exit(EXIT_FAILURE);
	if (!av[1])
		return (print_in_order(l_env));
	ret_val = add_exports_to_list(av, l_env, TRUE);
	free_char_env(*env);
	*env = list_to_env(l_env);
	return (ret_val);
}
// 
// int main(int ac, char **av, char **env)
// {
// 	t_env	**l_env;
// 	char	*boop[2];

// 	l_env = env_to_list(env);
// 	env = ft_tabdup(env);
// 	ft_env(boop, env);
// 	printf("___________________________________\n");
// 	ft_export(av, l_env, &env);
// 	printf("___________________________________\n");
// 	ft_env(boop, env);
// 	env_free_all_node(l_env);
// 	free_char_env(env);
// 	return (0);
// }
