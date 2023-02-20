/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:41:46 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/16 16:39:15 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
	returns index of first matching quote found
	Increment by 1 by default to avoir checking the same quote
	Else returns 0
*/
int	find_quotes(char *str, char matching_q)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == matching_q)
			return (i + 1);
		i++;
	}
	return (0);
}

int	is_quote(char c)
{
	if (c == S_QUOTE || c == D_QUOTE)
		return (1);
	return (0);
}

int	is_space_or_ht(char c)
{
	if (c == ' ' || c == '	')
		return (1);
	return (0);
}
