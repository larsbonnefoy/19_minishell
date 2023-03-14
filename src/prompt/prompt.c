/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:07:34 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/14 16:06:25 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/prompt.h"
#include "../../Includes/minishell.h"

static void	handle_prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_ret_val = 130;
	}
}

static void	handle_heredoc_child(int sig)
{
	if (sig == SIGINT)
	{
		// ft_putchar_fd('\n', 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		g_ret_val = 130;
		exit(130);
	}
}

static void	handle_heredoc_parent(int sig)
{
	if (sig == SIGINT)
	{
		// ft_putchar_fd('\n', 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		g_ret_val = 130;
	}
}

int	handle_signal(int i)
{
	struct sigaction	sc;

	if (i == 0)
	{
		sc.sa_handler = &handle_prompt;
		sigaction(SIGINT, &sc, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 1)
	{
		sc.sa_handler = &handle_heredoc_child;
		sigaction(SIGINT, &sc, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 2)
	{
		sc.sa_handler = &handle_heredoc_parent;
		sigaction(SIGINT, &sc, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}

static char	*get_line(void)
{
	char				*line;

	line = readline("\033[0;36mSea-Shell>\033[0m");
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
}

char	*prompt(void)
{
	char			*line;

	handle_signal(0);
	line = get_line();
	if (!line)
	{
		write(2, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	return (line);
}
