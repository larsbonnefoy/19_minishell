/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:20:13 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/16 11:31:57 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../src/libft/libft.h"
# include "env.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "prompt.h"

typedef struct s_simple_cmds
{
	char					**av;
	t_lexer					*redirections;
	int						n;
	int						pid;
	int						hdoc_fd;
	struct s_simple_cmds	*next;
}	t_simple_cmds;

t_simple_cmds	*create_simple_cmds(t_lexer *lexer);
void			destroy_simple_cmds(t_simple_cmds *cmd);
char			**make_local(char **av);
int				is_local(char *av);
int				lexer_to_cmd(t_lexer **lexer, t_simple_cmds *res, int i);
void			print_cmd(t_simple_cmds *cmd);

#endif
