/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:09:38 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/12 12:14:07 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

int	find_quotes(char *str, char matching_q);
char *join_substr(char *main_str, char *clean_str, int beg_sub_str, int length);
char *remove_sub_quotes(char *str);
int is_quote(char c);

/*
	Split the input string into words and tokens
		->Need to remove subsequent quotes of the same type first 
		->Check for alone standing quote and returns if quote error.
	Replace every whitespace that is not between strings to space
*/
t_lexer  *tokenize(char *input_string)
{
	t_lexer *lexer;
	char	*clean_str;

	lexer = NULL;
	clean_str = remove_sub_quotes(input_string);
	printf("cleaned string = %s\n", clean_str);
	return (lexer);
}

/*
	Remove subsequent quotes
	Send back every non-empty string enclosed by the same quotes
*/
char *remove_sub_quotes(char *str)
{
	int		curr_pos;
	int		beg_sub;
	int		next_matching_q;
	char	*clean_str;
	
	curr_pos = 0;
	beg_sub = curr_pos;
	clean_str = NULL;
	while (str[curr_pos])
	{
		while (!is_quote(str[curr_pos]) && str[curr_pos] != '\0') 
			curr_pos++;
		if (curr_pos != 0)
			clean_str = join_substr(str, clean_str, beg_sub, curr_pos - beg_sub);
		else if (is_quote(str[curr_pos]))
		{
			next_matching_q = find_quotes(str + curr_pos, str[curr_pos]);
			if (!next_matching_q)
				return (NULL);
			curr_pos += next_matching_q;
			clean_str = join_substr(str, clean_str, beg_sub, curr_pos - beg_sub);
		}
		curr_pos++;
		beg_sub = curr_pos;
	}
	return (clean_str);
}

/*
	returns index of first matching quote found
	else returns 0
*/
int	find_quotes(char *str, char matching_q)
{
	int i;

	i = 1;
	while (str[i] != '\0')	
	{
		if (str[i] == matching_q)
			return (i);	
		i++;
	}
	return (0);
}

int is_quote(char c)
{
	if (c == S_QUOTE || c == D_QUOTE)
		return (1);
	return (0);
}

char *join_substr(char *main_str, char *clean_str, int beg_sub_str, int length)
{
	char	*sub_str;
	char	*new_clean_str;

	new_clean_str = NULL;
	sub_str = ft_substr(main_str, beg_sub_str, length);
	printf("substr = %s\n", sub_str);
	new_clean_str = ft_strjoinf(clean_str, sub_str);
	return (new_clean_str);
}
