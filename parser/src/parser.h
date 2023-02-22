/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:20:13 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/21 12:08:10 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../src/minishell.h"

typedef struct s_simple_cmds
{
	char                    **av;
	//int                     (*builtin)(t_tools *, struct s_simple_cmds *);
	// int                     num_redirections;
	//char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
}	t_simple_cmds;

t_simple_cmds	*create_simple_cmd(t_lexer *lexer);

#endif