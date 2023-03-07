/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:45:24 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/07 09:03:48 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

static char	*format_path(char *str, char *pwd)
{
	char	*res;
	char	*tmp;

	if (!str)
		exit(EXIT_FAILURE);
	if (str[0] == '/')
		return (ft_strdup(str));
	if (str[0] == '\0')
		return (ft_strdup("/"));
	else
	{
		tmp = ft_strjoin(pwd, "/");
		res = ft_strjoin(tmp, str);
		free(tmp);
		return (res);
	}	
}

static void	set_pwds(char *old, t_env **l_env, char ***env)
{
	char	*new_pwd;
	char	new[1024];
	char	*(new_av[3]);
	char	*(old_av[3]);
	char	*old_pwd;

	if (!getcwd(new, 1024))
		exit(EXIT_FAILURE);
	new_pwd = ft_strjoin("PWD=", new);
	old_pwd = ft_strjoin("OLDPWD=", old);
	new_av[0] = "export";
	new_av[1] = new_pwd;
	new_av[2] = NULL;
	old_av[0] = "export";
	old_av[1] = old_pwd;
	old_av[2] = NULL;
	ft_export(new_av, env, l_env);
	free(new_pwd);
	ft_export(old_av, env, l_env);
	free(old_pwd);
}

int	ft_cd(char **av, char ***env, t_env **l_env)
{
	char	*home;
	char	old_pwd[1024];
	char	*new_pwd;

	home = ft_getenv("HOME", l_env);
	if (!getcwd(old_pwd, 1024))
		exit(EXIT_FAILURE);
	if (!av)
		exit(EXIT_FAILURE);
	if (!av[1] && !home)
		return (0);
	if (!av[1] && home)
		new_pwd = home;
	else
		new_pwd = format_path(av[1], old_pwd);
	if (chdir(new_pwd) == -1)
	{
		perror("cd");
		free(new_pwd);
		return (errno);
	}
	set_pwds(old_pwd, l_env, env);
	free(new_pwd);
	return (0);
}

// int	main(int ac,  char **av, char **env)
// {
// 	t_env	**l_env;
// 	env = ft_tabdup(env);
// 	l_env = env_to_list(env);
// 	ft_cd(av, &env, l_env);
// 	ft_pwd(av, &env, l_env);
// 	printf("pwd > [%s]\n", ft_getenv("PWD", l_env));
// 	printf("old_pwd > [%s]\n", ft_getenv("OLDPWD", l_env));
// 	free_char_env(env);
// 	env_free_all_node(l_env);	
// }
