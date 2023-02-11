/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:09:38 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/11 16:30:31 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
	Split the input string into words and tokens
	Need to keep elements between strings 
		->create a sub-string to the next quote
	   		->use split
		->store every element between quotes	
*/
t_lexer  *tokenize(char *input_string)
{
	t_lexer *lexer;
	char	**tab_values;
		
	tab_values = ft_split(input_string, ' ');
	return (lexer);
}



/*
	returns index of first quote found
	else returns 0
int	find_quotes(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')	
	{
		if (str[i] == '\'' || str[i] == '"')
			return (i);	
		i++;
	}
	return (0);
}
*/
