/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:08:25 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/10 19:50:59 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

# include "../src/libft/libft.h"
# include "env.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "prompt.h"
# include "executor.h"
# include "ft_echo.h"
# include "ft_env.h"
# include "ft_exit.h"
# include "ft_export.h"
# include "ft_pwd.h"
# include "ft_unset.h"

int		ft_cd(char **av, char ***env, t_env **l_env);
int		ft_unset(char **av, char ***env, t_env **l_env);
int		ft_env(char **av, char ***env, t_env **l_env);
int		ft_pwd(char **av, char ***env, t_env **l_env);
int		ft_echo(char **av, char ***env, t_env **l_env);
int		ft_exit(char **av, char ***env, t_env **l_env);
int		ft_export(char **av, char ***env, t_env **l_env);
int		ft_local(char **av, char ***env, t_env **l_env);

void	print_cmd(t_simple_cmds *cmd);

#endif