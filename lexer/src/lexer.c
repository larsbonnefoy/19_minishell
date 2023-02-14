/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:09:38 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/14 14:52:47 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void	add_to_lexer(char *str, t_lexer **lexer);
void	set_lexer(char *str, t_lexer **lexer);
int		is_token(char *str_to_add);

/*
	Split the input string into words and tokens
		->Need to remove subsequent quotes of the same type first (that are directly adjacent to a word)
		->Check for alone standing quote and returns if quote error.
	Add to the linked list t_lexer every elem of the string without white spaces except if between quotes
	Replace every whitespace that is not between strings to space
*/
t_lexer  *tokenize(char *input_string)
{
	t_lexer *lexer;
	char	*clean_str;

	lexer = NULL;
	clean_str = handle_sub_quotes(input_string);
	if (clean_str == NULL)
		return (NULL);
	printf("cleaned string = %s\n", clean_str);
	set_lexer(clean_str, &lexer);
	free(clean_str);
	return (lexer);
}

/*
 * checking for whitespaces, if quotes, jump to the next matching quote
 */
void set_lexer(char *str, t_lexer **lexer)
{
	int curr_pos;
	int beg_of_substr;
	char *str_to_add;
	(void) lexer;

	curr_pos = 0;
	while (str[curr_pos])
	{
		while(is_space_or_ht(str[curr_pos]))
			curr_pos++;
		beg_of_substr = curr_pos; 
		while(!is_space_or_ht(str[curr_pos]) && str[curr_pos] != '\0')
		{
			if (is_quote(str[curr_pos]))
				curr_pos += find_quotes(str + curr_pos, str[curr_pos]);
			else
				curr_pos++;
		}
		str_to_add = ft_substr(str, beg_of_substr, curr_pos - beg_of_substr);
		if (str_to_add[0] != '\0')
			add_to_lexer(str_to_add, lexer);
	}
	lexer_print_list(lexer);
}

void add_to_lexer(char *str_to_add, t_lexer **lexer)
{
	t_lexer *new_node;
	e_token	token_value;

	token_value = is_token(str_to_add);
	if (token_value != 0)
	{
		free(str_to_add);
		str_to_add = NULL;	
	}	
	new_node = lexer_new_node(str_to_add, token_value);
	lexer_add_back(lexer, new_node);	
}

/*
 * Tokens can be set next to directly next to words
 */
int is_token(char *str_to_add)
{
	if (ft_strlen(str_to_add) == 2)
	{
		if (str_to_add[0] == '>' && str_to_add[1] == '>')
			return (D_GREATER);
		if (str_to_add[0] == '<' && str_to_add[1] == '<')
			return (D_GREATER);
	}
	else if (str_to_add[0] == '|')
		return (PIPE);
	else if (str_to_add[0] == '>')
		return (GREATER);
	else if (str_to_add[0] == '<')
		return (LOWER);
	return (NOT_A_TOKEN);
}
