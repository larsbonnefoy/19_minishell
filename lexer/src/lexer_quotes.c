/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:39:40 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/17 12:43:06 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
	Remove subsequent quotes that are not alone-standing 
		->if they are empty && direclty next to char != from space or ht
	Sends back every non-empty string enclosed by the same quotes
*/
char	*handle_sub_quotes(char *str)
{
	int		i;
	int		prev_i;
	int		beg_sub;
	char	*clean_str;

	i = 0;
	beg_sub = i;
	clean_str = ft_calloc_exit(1, sizeof(char));
	while (str[i])
	{
		prev_i = i;
		if (is_quote(str[i]))
		{
			i += find_quotes(str + i, str[i]);
			if (i == prev_i)
				return (NULL);
		}
		else
			while (str[i] != '\0' && !is_quote(str[i]))
				i++;
		clean_str = join_substr(str, clean_str, beg_sub, i - beg_sub);
		beg_sub = i;
	}
	return (clean_str);
}

/*
 *	Joins in clean_str chars from main_str[beg_sub_str; beg_sub_str + len] 
 *	FREE SUBSTR ? or leaks?
 */
char	*join_substr(char *main_str, char *clean_str, int beg_sub_str, int len)
{
	char	*sub_str;
	char	*new_clean_str;

	//leak ici
	sub_str = ft_substr(main_str, beg_sub_str, len);
	if (sub_str == NULL)
		return (NULL);
	if (!(remove_quotes(main_str, sub_str, beg_sub_str)))
	{
		new_clean_str = ft_strjoin_ff(clean_str, sub_str);
		return (new_clean_str);
	}
	else
	{
		free(sub_str);
		return (clean_str);
	}
}

/*
 * Returns 1 the quotes have to removed
 * Else retunrs 0
 */
int	remove_quotes(char *main_str, char *sub_str, int beg_sub_str)
{
	int		len;
	char	elem_left;
	char	elem_right;

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
