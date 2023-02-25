/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:10:26 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/25 17:35:37 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include"../../libft/libft.h"
# include "../../lexer/src/lexer.h"
# include "../../parser/src/parser.h"
# include <sys/types.h>
# include <sys/wait.h>


//executor
void	executor(t_simple_cmds *cmd, char **env);
//ft_execve
void ft_execve(char **av, char **env);
char *get_access_path(char **av, char *path);
#endif
