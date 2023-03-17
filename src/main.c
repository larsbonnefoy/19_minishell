/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:16:04 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/17 14:59:49 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "../Includes/all.h"

static void	set_shell_lvl(t_env **l_env, char ***env)
{
	char	*value;
	int		tmp;
	char	*av[2];

	av[0] = "ft_export";
	value = ft_getenv("SHLVL", l_env);
	tmp = ft_atoi(value);
	av[1] = ft_itoa(tmp + 1);
	ft_export(av, env, l_env);
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	char			*clean;
	t_env			**l_env;
	t_lexer			*lexer;
	t_simple_cmds	*cmd;

	g_ret_val = 0;
	env = ft_tabdup(env);
	l_env = env_to_list(env);
	while (1)
	{
		line = prompt();
		lexer = tokenize(line);
		free(line);
		lexer_to_expander(&lexer, l_env);
		cmd = create_simple_cmds(lexer);
		lexer_clear_list(&lexer);
		executor(cmd, &env, l_env);
		if (cmd)
			destroy_simple_cmds(cmd);
	}
	free_char_tab(env);
	env_free_all_node(l_env);
}
