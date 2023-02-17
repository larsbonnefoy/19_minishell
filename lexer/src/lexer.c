/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:09:38 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/17 13:05:35 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void	add_to_lexer(char *str, t_lexer **lexer);
void	set_lexer(char *str, t_lexer **lexer);
int		is_token(char *str_to_add);
int		add_to_pos(char *str, int start_pos);

/*
	Split the input string into words and tokens
		->Need to remove subsequent quotes of the same type first 
			(that are directly adjacent to a word)
		->Check for alone standing quote and returns quote error.
*/
t_lexer	*tokenize(char *input_string)
{
	t_lexer	*lexer;
	char	*clean_str;

	lexer = NULL;
	clean_str = handle_sub_quotes(input_string);
	if (clean_str == NULL)
		return (NULL);
	set_lexer(clean_str, &lexer);
	free(clean_str);
	return (lexer);
}

/*
 * Returns linked list lexer where each node is a word or a token
 * Skip withespaces
 * If quotes, jump to the next matching quote
 * If token, creates new substr with token
 */
void	set_lexer(char *str, t_lexer **lexer)
{
	int		i;
	int		beg_substr;
	char	*str_to_add;

	i = 0;
	while (str[i])
	{
		while (is_space_or_ht(str[i]))
			i++;
		beg_substr = i;
		if (is_token(&str[i]))
		{
			i += add_to_pos(str, i);
			str_to_add = ft_substr(str, beg_substr, i - beg_substr);
			add_to_lexer(str_to_add, lexer);
			beg_substr = i;
		}
		while (!is_space_or_ht(str[i]) && !is_token(&str[i]) && str[i] != '\0')
			i += add_to_pos(str, i);
		//memory leak
		str_to_add = ft_substr(str, beg_substr, i - beg_substr);
		if (str_to_add[0] != '\0')
			add_to_lexer(str_to_add, lexer);
	}
	lexer_print_list(lexer);
}

/*
 * Adds the substr to the lexer list
 * If the substr is a token, adds its enum value in the list,
 * frees the substring and sets the string to be added to null
 */
void	add_to_lexer(char *str_to_add, t_lexer **lexer)
{
	t_lexer	*new_node;
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
 * Returns enum value of token when one is found, else returns 0;
 */
int	is_token(char *str_to_add)
{	
	if (str_to_add[0] == '\0')
		return (NOT_A_TOKEN);
	if (str_to_add[0] == '>' && str_to_add[1] == '>')
		return (D_GREATER);
	else if (str_to_add[0] == '<' && str_to_add[1] == '<')
		return (D_GREATER);
	else if (str_to_add[0] == '|')
		return (PIPE);
	else if (str_to_add[0] == '>')
		return (GREATER);
	else if (str_to_add[0] == '<')
		return (LOWER);
	return (NOT_A_TOKEN);
}

/*
 * Retuns the increment to add to the current_position
 */
int	add_to_pos(char *str, int start_pos)
{
	int		i;
	e_token	token;

	if (str[start_pos] == '\0' || is_space_or_ht(str[start_pos]))
		return (0);
	i = 0;
	if (is_quote(str[start_pos]))
		return (i += find_quotes(str + start_pos, str[start_pos]));
	token = is_token(&str[start_pos]);
	if (token)
	{
		if (token == D_GREATER || token == D_LOWER)
			return (i += 2);
		else
			return (i + 1);
	}
	else
		return (i + 1);
}
