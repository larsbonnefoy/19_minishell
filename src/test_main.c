/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:16:04 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/25 11:47:32 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_simple_cmds *cmd)
{
	int	k;
	int	j;

	k = -1;
	while (cmd)
	{
		j = -1;
		printf("cmd%d av : [", ++k);
		while (cmd->av && cmd->av[++j])
		{
			if (cmd->av[j + 1])
				printf("%s, ", cmd->av[j]);
			else 
				printf("%s]", cmd->av[j]);
		}
		if (cmd->redirections)
		{
			printf("\t");
			printf("redirection :");
			lexer_print_list(&cmd->redirections);
		}
		printf("\n");
		cmd = cmd->next;		
	}
}

int main(int argc, char **argv, char **env)
{
	char			*line;
	char			*clean;

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
		if (ft_strncmp("exit", line, 4) == 0)
			break ;
		printf("input line = %s\n", line);
		printf("-----------------------\n");
		lexer = tokenize(line);
		free(line);
		lexer_print_list(&lexer);
		printf("-----------------------\n");
		lexer_to_expander(lexer, l_env);
		lexer_print_list(&lexer);
		printf("-----------------------\n");
		cmd = create_simple_cmds(lexer);
		lexer_clear_list(&lexer);
		printf("-----------------------\n");
		print_cmd(cmd);
		printf("-----------------------\n");
		if (cmd)
			destroy_simple_cmds(tmp);
	}
	env_free_all_node(l_env);
	return (0);
}
