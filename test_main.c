/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:16:04 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/20 09:58:19 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char *get_line(void)
{
	char *line;

	line = readline("\033[0;36mSea-Shell>\033[0m");

	return (line);
}

void	expand_lexer(t_lexer *lexer, t_env **env)
{
	char	*clean;
	t_lexer	*head;
	char	sys_str[200] = "echo echo : ";

	head = lexer;
	while (lexer && lexer->str)
	{
		clean = cleaner(lexer->str, env);
		printf("input :%s\n", lexer->str);
		printf("cleaned :%s\n", clean);
		free(clean);
		strcat(sys_str, lexer->str);//
		system(sys_str);
		lexer = lexer->next;
	}
	lexer = head;
}

int main(int argc, char **argv, char **env)
{
	char *line;
	char *clean;
	(void) argc;
	(void) argv;
	int	i = 0;
	t_env	**local;
	t_env	*node2;
	t_env	*node3;
	t_lexer *lexer;

	local = env_to_list(env);
	node2 = env_new(ft_strdup("?"), ft_strdup("hihi workey"), 0);
	node3 = env_new(ft_strdup("?"), ft_strdup("POG"), 0);
	env_addfront(node2, local);
	while (1)
	{
		line = get_line();
		printf("input line = %s\n", line);	
		lexer = tokenize(line);
		lexer_print_list(&lexer);
		expand_lexer(lexer, local);
		lexer_print_list(&lexer);
		
		free(line);
		lexer_clear_list(&lexer);
		if (i == 3)
			env_reassign(node3, local);
		i++;
	}
	env_free_all_node(local);
	return(0);
}
