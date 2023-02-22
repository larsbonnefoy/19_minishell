/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:16:04 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/22 17:59:00 by hdelmas          ###   ########.fr       */
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
		printf("-----------------------\n");
		lexer_to_expander(lexer, l_env);
		lexer_print_list(&lexer);
		printf("-----------------------\n");
		cmd = create_simple_cmds(lexer);
		lexer_clear_list(&lexer);
		j = -1;
		printf("-----------------------\n");
		tmp = cmd;
		k = 0;
		while (cmd)
		{
			j = -1;
			printf("cmd%d av : [", ++k);
			while (cmd->av && cmd->av[++j])
			{
				if (cmd->av[j + 1])
					printf("%s, ", cmd->av[j]);
				else 
					printf("%s]\n", cmd->av[j]);
			}
			if (cmd->redirections)
			{
				printf("-----------------------\n");
				printf("redirection : \n");
				lexer_print_list(&cmd->redirections);
			}
			printf("-----------------------\n");
			cmd = cmd->next;			
		}
		if (tmp)
			destroy_simple_cmds(tmp);
		if (i == 3)
			env_reassign(node3, l_env);
		i++;
	}
	if (i < 3 )
		env_free_node(node3);
	env_free_all_node(l_env);
	return (0);
}
