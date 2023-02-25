/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:16:04 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/25 17:41:23 by hdelmas          ###   ########.fr       */
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
	char			*line;
	char			*clean;
	int				i;
	int				j;
	t_env			**l_env;
	t_env			*node2;
	t_env			*node3;
	t_lexer			*lexer;
	t_simple_cmds	*cmd;
	t_simple_cmds	*tmp;

	(void)argc;
	(void)argv;
	l_env = env_to_list(env);
	node2 = env_new(ft_strdup("?"), ft_strdup("0"), 0);
	env_addfront(node2, l_env);
	line = "";
	while (1)
	{
		line = prompt();
		printf("{%s}\n", line);
		if (ft_strncmp("exit", line, 4) == 0)
			break ;
//		printf("input line = %s\n", line);
//		printf("--------LEXER---------\n");
		lexer = tokenize(line);
		free(line);
//		lexer_print_list(&lexer);
//		printf("--------EXPAND--------\n");
		lexer_to_expander(lexer, l_env);
//		lexer_print_list(&lexer);
		cmd = create_simple_cmds(lexer);
		lexer_clear_list(&lexer);
//		printf("----------CMD----------\n");
		tmp = cmd;
		executor(tmp, env);
		tmp = cmd;
		if (tmp)
			destroy_simple_cmds(tmp);
	}
	env_free_all_node(l_env);
	return (0);
}
