/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:07:34 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/24 18:23:46 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,*/

#include "prompt.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}


void	handle_signal(void)
{
	struct sigaction	sa;
	
	sa.sa_handler = &handle_sig;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
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
	return (line);
}
