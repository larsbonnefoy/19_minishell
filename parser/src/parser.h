/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:20:13 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/25 15:07:15 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include"../../libft/libft.h"
# include "../../lexer/src/lexer.h"

typedef struct s_simple_cmds
{
	char					**av;
	t_lexer					*redirections;
	int						n;
	int						pid;
	struct s_simple_cmds	*next;
}	t_simple_cmds;

t_simple_cmds	*create_simple_cmds(t_lexer *lexer);
void			destroy_simple_cmds(t_simple_cmds *cmd);

#endif
