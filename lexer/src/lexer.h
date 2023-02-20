/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:43:01 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/20 09:13:23 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#define S_QUOTE 39
#define D_QUOTE 34

# include<stdlib.h>
# include"../../libft/libft.h"

/*
	Ascii values of | < >
*/

typedef enum token
{
	PIPE = 124,
	GREATER = 62,
	LOWER = 60,

}	e_token;

typedef struct lexer
{
	char			*str;
	e_token			token;
	struct lexer 	*next;

}	t_lexer;

t_lexer	*tokenize(char *input_string);
t_lexer	*lexer_new_node(char *str, e_token token);
void 	lexer_add_back(t_lexer **lexer_list, t_lexer *new_node);
void	lexer_clear_list(t_lexer **lexer_list);
#endif
