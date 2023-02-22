/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:10:26 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/22 11:14:54 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include"../../libft/libft.h"
typedef struct s_simple_cmds
{
    char                    **av;
    //int                     (*builtin)(t_tools *, struct s_simple_cmds *);
    int                     num_redirections;
    //char                    *hd_file_name;
    //t_lexer                 *redirections;
    struct s_simple_cmds    *next;
    //struct s_simple_cmds    *prev;
}    t_simple_cmds;
#endif
