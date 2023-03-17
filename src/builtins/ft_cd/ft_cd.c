/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:45:24 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/17 15:15:49 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

static int	err(int i, char *new_pwd)
{
	if (i == 1)
		ft_putendl_fd("minishell: cd: too many arguments", 2);
	else if (i == 2)
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	else if (i == 3)
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	else if (i == 4)
	{
		perror("cd");
		free(new_pwd);
		return (errno);
	}
	else if (i == 5)
	{
		ft_putstr_fd("minishell: cd: error retrieving ", 2);
		ft_putstr_fd("current directory: getcwd: cannot access parent ", 2);
		ft_putendl_fd("directories:No such file or directory", 2);
		return (0);
	}
	return (1);
}

static char	*dup_errcheck(char *str, int i)
{
	char	*res;

	if (!str)
	{
		err(i, NULL);
		return (NULL);
	}
	res = ft_strdup(str);
	return (res);
}

static char	*format_path(char *str, char *pwd, char *home, t_env **l_env)
{
	char	*res;
	char	*tmp;
	char	*old;

	old = ft_getenv("OLDPWD", l_env);
	if (!str)
		exit(EXIT_FAILURE);
	if (str[0] == '/')
		return (ft_strdup(str));
	if (str[0] == '\0')
		return (ft_strdup("/"));
	if (ft_strncmp(str, "-", ft_strlen(str)) == 0)
		return (dup_errcheck(old, 3));
	if (ft_strncmp(str, "--", ft_strlen(str)) == 0)
		return (dup_errcheck(home, 2));
	if (pwd[0] != '\0')
	{
		tmp = ft_strjoin(pwd, "/");
		res = ft_strjoin(tmp, str);
		free(tmp);
		return (res);
	}
	else
		err(5, NULL);
	return (NULL);
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
	char	curr_pwd[1024];
	char	*new_pwd;

	home = ft_getenv("HOME", l_env);
	if (!getcwd(curr_pwd, 1024))
		curr_pwd[0] = '\0';
	if (!av)
		exit(EXIT_FAILURE);
	if (av[1] && av[2])
		return (err(1, NULL));
	if (!av[1] && !home)
		return (err(2, NULL));
	if (!av[1] && home)
		new_pwd = ft_strdup(home);
	else
		new_pwd = format_path(av[1], curr_pwd, home, l_env);
	if (!new_pwd || *new_pwd == '\0')
		return (1);
	if (chdir(new_pwd) == -1)
		return (err(4, new_pwd));
	set_pwds(curr_pwd, l_env, env);
	free(new_pwd);
	return (0);
}
