/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:16:04 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/13 09:16:48 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "smpcmd.h"

char *get_line(void)
{
	char *line;

	line = readline("\033[0;36mSea-Shell>\033[0m");

	return (line);
}

int main(int argc, char **argv, char **env)
{
	char *line;
	char *clean;
	(void) argc;
	(void) argv;
	int	i =-1;
//	while (env[++i])
//		printf("%s\n",env[i]);
	//printf("%s\n",getenv("?"));
	while (1)
	{
		char sys_str[200] = "echo echo :";
		line = get_line();
		clean = cleaner(line);
		printf("input :%s\n", line);
		printf("cleaned :%s\n", clean);
		free(clean);
		strcat(sys_str, line);
		system(sys_str);
		free(line);
	}
	return(0);
}