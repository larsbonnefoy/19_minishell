/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:16:04 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/17 15:48:10 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
	t_env	**local;

	local = env_to_list(env);
	*local = env_new("TEST", "test_value", 0);
	t_env *node2;
	node2 = env_new("?", "hihi workey", 0);
	env_addfront(node2, local);
	while (1)
	{
		char sys_str[200] = "echo echo : ";
		line = get_line();
		clean = cleaner(line, local);
		printf("input :%s\n", line);
		printf("cleaned :%s\n", clean);
		free(clean);
		strcat(sys_str, line);
		system(sys_str);
		free(line);
	}
	env_free_all_node(local);
	return(0);
}
