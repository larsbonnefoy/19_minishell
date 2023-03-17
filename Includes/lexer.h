/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:43:01 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/17 13:54:20 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define S_QUOTE 39
# define D_QUOTE 34

# include<stdlib.h>
# include<stdio.h>
# include"../src/libft/libft.h"

/*
	token have a value between 1 and 5
*/
typedef enum e_token
{
	NOT_A_TOKEN = 0,
	PIPE,
	GREATER,
	D_GREATER,
	LOWER,
	D_LOWER,
}	t_token;

typedef struct s_lexer
{
	char			*str;
	t_token			token;
	int				hdoc_exp;
	struct s_lexer	*next;
}	t_lexer;

t_lexer	*tokenize(char *input_string);

//lexer_quotes
char	*handle_sub_quotes(char *str);

//lexer_quotes_utils
int		find_quotes(char *str, char matching_q);
int		is_space_or_ht(char c);
int		is_quote(char c);

//lexer_list_management
t_lexer	*lexer_new_node(char *str, t_token token);
void	lexer_add_back(t_lexer **lexer_list, t_lexer *new_node);
void	lexer_print_list(t_lexer **lexer_list);
void	lexer_clear_list(t_lexer **lexer_list);
//
int		syntax_error(t_lexer **lexer);
#endif
