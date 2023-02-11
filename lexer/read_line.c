/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:48:00 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/11 14:55:43 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_line(void)
{
	char *line;

	line = readline("Sea-Shell>");

	return (line);
}

int main(int argc, char **argv)
{
	char *line;

	while (1)
	{
		line = get_line();
		printf("%s\n", line);	
		free(line);
	}
	return(0);
}

