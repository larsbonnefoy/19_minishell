/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:10:26 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/23 13:14:07 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include"../../libft/libft.h"
# include "../../lexer/src/lexer.h"
# include "../../parser/src/parser.h"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
//executor
void	executor(t_simple_cmds *cmd, char **env);
//ft_execve
void ft_execve(char **av, char **env, int debug_stdout);
char *get_access_path(char **av, char *path);
#endif