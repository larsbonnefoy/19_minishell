/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:07:34 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/24 15:30:39 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,*/

#include "prompt.h"

void	handle_sigint(int sig)
{
	// rl_on_new_line();
	// rl_replace_line("test\n", 0);
	// rl_redisplay();
	rl_on_new_line();
	rl_replace_line("\n", 0);
	rl_redisplay();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
}

void	handle_signal(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

char	*get_line(void)
{
	char				*line;

	line = readline("\033[0;36mSea-Shell>\033[0m");
	printf("[%s], [%zu]\n",line, ft_strlen(line));
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
}

char	*prompt(void)
{
	char	*line;

	handle_signal();
	line = get_line();
	// handle_signal();
	return (line);
}
