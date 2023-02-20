/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:16:04 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/20 17:44:58 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_line(void)
{
	char *line;

	line = readline("\033[0;36mSea-Shell>\033[0m");

	return (line);
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	*clean;
	int		i;
	t_env	**l_env;
	t_env	*node2;
	t_env	*node3;
	t_lexer	*lexer;

	(void)argc;
	(void)argv;
	i = 0;
	l_env = env_to_list(env);
	node2 = env_new(ft_strdup("?"), ft_strdup("hihi workey"), 0);
	node3 = env_new(ft_strdup("?"), ft_strdup("POG"), 0);
	env_addfront(node2, l_env);
	line = "";
	while (1)
	{
		line = get_line();
		if (ft_strncmp("exit", line, 4) == 0)
			break ;
		printf("input line = %s\n", line);
		lexer = tokenize(line);
		free(line);
		lexer_print_list(&lexer);
		printf("\n\n");
		lexer_to_expander(lexer, l_env);
		lexer_print_list(&lexer);

		lexer_clear_list(&lexer);
		if (i == 3)
			env_reassign(node3, l_env);
		i++;
	}
	env_free_all_node(l_env);
	return (0);
}
