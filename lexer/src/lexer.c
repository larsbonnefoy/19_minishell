/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:09:38 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/13 15:13:15 by lbonnefo         ###   ########.fr       */
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
		->Need to remove subsequent quotes of the same type first (that are directly adjacent to a word)
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
	Remove subsequent quotes that are not alone-standing 
		->if they are empty && direclty next to char ! from space or ht
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
		printf("-------------BEG---------------\n");
		printf("main str  = %s\n", str);
		printf("curr_pos  = %d\n", curr_pos);
		next_matching_q = 0;
		if (is_quote(str[curr_pos]))
		{
			next_matching_q = find_quotes(str + curr_pos, str[curr_pos]);
			if (next_matching_q == 0) //Should check for non closed quotes
				return (NULL);
			printf("next_matching q = %d\n", next_matching_q);
			clean_str = join_substr(str, clean_str, beg_sub, next_matching_q);
		}
		else
		{
			while (str[curr_pos] != '\0' && !is_quote(str[curr_pos]))
				curr_pos++;
			printf("copy %d char\n", curr_pos);	
			clean_str = join_substr(str, clean_str, beg_sub, curr_pos - beg_sub);
		}
		curr_pos = curr_pos + next_matching_q;
		beg_sub = curr_pos;
		printf("cleaned str = %s\n", clean_str);
		printf("-------------END---------------\n");
	}
	return (clean_str);
}

/*
	returns index of first matching quote found
	Increment by 1 by default to avoir checking the same quote
	Else returns 0
*/
int	find_quotes(char *str, char matching_q)
{
	int i;

	i = 1;
	printf("str find_q = %s\n", str);
	while (str[i] != '\0')	
	{
		if (str[i] == matching_q)
			return (i + 1);	
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

int is_space_or_ht(char c)
{
	if (c == ' ' || c == '	')
		return (1);
	return (0);
}

/*
 *	Joins in clean_str chars from main_str[beg_sub_str; beg_sub_str + length] 
 *
 */
char *join_substr(char *main_str, char *clean_str, int beg_sub_str, int length)
{
	printf("----------SUB------------\n");
	char	*sub_str;
	char	*new_clean_str;

	printf("main str  = %s\n", main_str);
	printf("beg_sub_str  = %d\n", beg_sub_str);
	printf("length  = %d\n", length);
	sub_str = ft_substr(main_str, beg_sub_str, length);
	if (sub_str == NULL)
		return (NULL);
	printf("substr = %s\n", sub_str);
	new_clean_str = ft_strjoinf(clean_str, sub_str);
	//free(sub_str);
	return (new_clean_str);
}

/*
int leave_quotes(char *str, int beg_sub_str)
{
	int len;

	len = ft_strlen(str);
	if (len == 2)
	{
		if (is_quote(str[0]) && is_quote(str[1]))
		{
			if (beg_sub_str == 0) //just check to the right
				
			else if (str[beg_sub_str + 1] == '\0') //just check to the left

			else
								
		
		}
	
	}
}
/*
 *  if len = 2
 *		if str[0] et str[1] sont des quotes
 *			if left ou right char different de ht ou space 
 *				alors join pas
 */
