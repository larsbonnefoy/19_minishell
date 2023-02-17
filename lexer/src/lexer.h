/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:43:01 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/17 13:05:39 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#define S_QUOTE 39
#define D_QUOTE 34

# include<stdlib.h>
# include<stdio.h>
# include"../../libft/libft.h"

/*
	Ascii values of | < >
	>> and << are double the ascii value of > and <
*/
typedef enum token
{
	NOT_A_TOKEN = 0,
	PIPE,
	GREATER,
	D_GREATER,
	LOWER,
	D_LOWER,

}	e_token;

typedef struct lexer
{
	char			*str;
	e_token			token;
	struct lexer 	*next;

}	t_lexer;

t_lexer  *tokenize(char *input_string);

//lexer_quotes
char	*handle_sub_quotes(char *str);
char	*join_substr(char *main_str, char *clean_str, int beg_sub_str, int length);
int		remove_quotes(char *main_str, char *sub_str, int beg_sub_str);

//lexer_quotes_utils
int		find_quotes(char *str, char matching_q);
int		is_space_or_ht(char c);
int		is_quote(char c);

//lexer_list_management
t_lexer	*lexer_new_node(char *str, e_token token);
void	lexer_add_back(t_lexer **lexer_list, t_lexer *new_node);
void	lexer_print_list(t_lexer **lexer_list); 
void	lexer_clear_list(t_lexer **lexer_list);
//
#endif
