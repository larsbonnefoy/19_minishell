/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:33:19 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/20 18:19:12 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H        

# include "../lexer/lexer.h"

typedef struct s_simple_cmds
{
	char                    **tab;
	//int                     (*builtin)(t_tools *, struct s_simple_cmds *);
	int                     num_redirections;
	//char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

# endif
