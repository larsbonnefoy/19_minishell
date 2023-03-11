/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:23:08 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/10 19:12:26 by hdelmas          ###   ########.fr       */
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

// int main(int ac, char **av, char **env)
// {
// 	t_env	**l_env;
// 	char	*boop[2];
// 	char	**un;

// 	un = ft_malloc(sizeof(char *) * 4);
// 	un[0] = ft_strdup("ft_unset");
// 	un[1] = ft_strdup("TERM_SESSION_ID");
// 	un[2] = ft_strdup("ARG");
// 	un[3] = NULL;
// 	l_env = env_to_list(env);
// 	boop[0] = "ft_env";
// 	boop[1] = NULL;
// 	env = ft_tabdup(env);
// 	ft_env(boop, env);
// 	printf("___________________________________\n");
// 	ft_export(av, l_env, &env);
// 	printf("___________________________________\n");
// 	ft_env(boop, env);
// 	printf("___________________________________\n");
// 	ft_unset(un, l_env, &env);
// 	ft_env(boop, env);
// 	printf("___________________________________\n");
// 	env_free_all_node(l_env);
// 	free_char_tab(env);
// 	return (0);
// }