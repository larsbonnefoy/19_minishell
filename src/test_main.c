/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:16:04 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/23 16:15:03 by lbonnefo         ###   ########.fr       */
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
	int				k;
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
	i = 0;
	while (1)
	{
		line = get_line();
		if (ft_strncmp("exit", line, 4) == 0)
			break ;
		printf("input line = %s\n", line);
		printf("--------LEXER---------\n");
		lexer = tokenize(line);
		free(line);
		lexer_print_list(&lexer);
		printf("--------EXPAND--------\n");
		lexer_to_expander(lexer, l_env);
		lexer_print_list(&lexer);
		cmd = create_simple_cmds(lexer);
		lexer_clear_list(&lexer);
		printf("----------CMD----------\n");
		tmp = cmd;
		k = 0;
		printf("cmd number = %d\n", i);
		executor(cmd, env);
		if (tmp)
			destroy_simple_cmds(tmp);
		i++;
	}
	env_free_all_node(l_env);
	return (0);
}
