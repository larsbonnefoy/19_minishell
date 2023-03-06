/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:10:26 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/06 11:17:56 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include "../src/libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include <fcntl.h>

//executor
void	executor(t_simple_cmds *cmd, char **env);
//ft_execve
void ft_execve(char **av, char **env);
char *get_access_path(char **av, char *path);
//out_redir.c
int get_out_fd(t_simple_cmds *cmd, int pipe_write);
char *get_out_file(t_simple_cmds *cmd);
int get_out_token(t_simple_cmds *cmd, char *file);
int is_outfile(t_lexer *redirections);
//in_redir.c
int get_in_fd(t_simple_cmds *cmd,int fd_in);
int is_infile(t_lexer *redirection);
#endif
