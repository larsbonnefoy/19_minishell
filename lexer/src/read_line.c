/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:48:00 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/17 13:06:14 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

char *get_line(void)
{
	char *line;

	line = readline("\033[0;36mSea-Shell>\033[0m");

	return (line);
}

int main(int argc, char **argv)
{
	char *line;
	(void) argc;
	(void) argv;
	t_lexer *lexer;
	//while (1)
	//{
		line = get_line();
		printf("input line = %s\n", line);	
		lexer = tokenize(line);
		free(line);
		lexer_clear_list(&lexer);
	//}
	return(0);
}

