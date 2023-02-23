/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:10:26 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/23 11:34:52 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include"../../libft/libft.h"
# include "../../lexer/src/lexer.h"

typedef struct s_simple_cmds
{
    char                    **av;
    t_lexer                 *redirections;
    struct s_simple_cmds    *next;
}    t_simple_cmds;

void executor(t_simple_cmds *cmd, char **env);

//ft_execve
void ft_execve(char **av, char **env);
char *get_access_path(char **av, char *path);
#endif
