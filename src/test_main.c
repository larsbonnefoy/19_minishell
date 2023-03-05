/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:16:04 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/05 19:43:59 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	print_cmd(t_simple_cmds *cmd)
{
	int	k;
	int	j;

	k = -1;
	while (cmd)
	{
		j = -1;
		printf(">n = %i\n",cmd->n);
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
	struct termios	term;

	(void)argc;
	(void)argv;
	// env = lstrdup(env)
	l_env = env_to_list(env);
	node2 = env_new(ft_strdup("?"), ft_strdup("0"), 0);
	env_addfront(node2, l_env);
	line = "";
	while (1)
	{
		line = prompt(&term);
		if (ft_strncmp("exit", line, 4) == 0)
			break ;
		printf("input line = %s\n", line);
		printf("-----------------------\n");
		printf("lexer ouput:\n");
		lexer = tokenize(line);
		free(line);
		lexer_print_list(&lexer);
		printf("-----------------------\n");
		printf("expander ouput:\n");
		lexer_to_expander(lexer, l_env);
		lexer_print_list(&lexer);
		printf("-----------------------\n");
		printf("simple_cmd ouput:\n");
		cmd = create_simple_cmds(lexer);
		lexer_clear_list(&lexer);
		print_cmd(cmd);
		printf("-----------------------\n");
		printf("execution output:\n");
		executor(cmd, env);
		printf("-----------------------\n");
		if (cmd)
			destroy_simple_cmds(cmd);
	}
	env_free_all_node(l_env);
	return (0);
}
