/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:39:40 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/14 09:59:49 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
	Remove subsequent quotes that are not alone-standing 
		->if they are empty && direclty next to char ! from space or ht
	Send back every non-empty string enclosed by the same quotes
*/
char *handle_sub_quotes(char *str)
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
		next_matching_q = 0;
		if (is_quote(str[curr_pos]))
		{
			next_matching_q = find_quotes(str + curr_pos, str[curr_pos]);
			if (next_matching_q == 0) //Should check for non closed quotes
				return (NULL);
			clean_str = join_substr(str, clean_str, beg_sub, next_matching_q);
		}
		else
		{
			while (str[curr_pos] != '\0' && !is_quote(str[curr_pos]))
				curr_pos++;
			clean_str = join_substr(str, clean_str, beg_sub, curr_pos - beg_sub);
		}
		curr_pos = curr_pos + next_matching_q;
		beg_sub = curr_pos;
	}
	return (clean_str);
}

/*
 *	Joins in clean_str chars from main_str[beg_sub_str; beg_sub_str + length] 
 *
 */
char *join_substr(char *main_str, char *clean_str, int beg_sub_str, int length)
{
	char	*sub_str;
	char	*new_clean_str;

	sub_str = ft_substr(main_str, beg_sub_str, length);
	if (sub_str == NULL)
		return (NULL);
	if (!(remove_quotes(main_str, sub_str, beg_sub_str)))
	{
		new_clean_str = ft_strjoinf(clean_str, sub_str); //malloc protec
		return (new_clean_str);
	}
	else
	{
		free(sub_str);
		return (clean_str);
	}
	//free(sub_str);
	//??
}

/*
 * Returns 1 the quotes have to removed
 * Else retunrs 0
 * has to work with ""
 */
int remove_quotes(char *main_str, char *sub_str, int beg_sub_str)
{
	int len;
	char elem_left;
	char elem_right;

	len = ft_strlen(sub_str);
	if (len != 2 || !(is_quote(sub_str[0]) && is_quote(sub_str[1])))
		return (0);
	elem_right = main_str[beg_sub_str + len];
	if (beg_sub_str != 0)
		elem_left = main_str[beg_sub_str -1];
	if (beg_sub_str == 0) 
	{
		if (is_space_or_ht(elem_right) || ft_strlen(main_str) == 2)	
			return (0);
	}
	else if (main_str[beg_sub_str + len] == '\0') 
	{
		if (is_space_or_ht(elem_left))	
			return (0);
	}
	else
		if (is_space_or_ht(elem_left) && is_space_or_ht(elem_right))
			return (0);
	return (1);
}
