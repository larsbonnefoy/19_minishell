/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:10:26 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/06 15:35:45 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include "../src/libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "ft_echo.h"
# include "ft_env.h"
# include "ft_exit.h"
# include "ft_export.h"
# include "ft_pwd.h"
# include "ft_unset.h"
# include <fcntl.h>

//executor
void	executor(t_simple_cmds *cmd, char **env, t_env **l_env);
//ft_execve
void 	ft_execve(char **av, char **env, t_env **l_env);
int		is_self_builtin(char *func_name);
int		exec_s_built(char **av, char **env, t_env **l_env, int self_built_nb);
//out_redir.c
int		get_out_fd(t_simple_cmds *cmd, int pipe_write);
char	*get_out_file(t_simple_cmds *cmd);
int		get_out_token(t_simple_cmds *cmd, char *file);
int		is_outfile(t_lexer *redirections);
//in_redir.c
int		get_in_fd(t_simple_cmds *cmd,int fd_in);
int		is_infile(t_lexer *redirection);
#endif
