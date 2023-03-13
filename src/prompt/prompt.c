/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:07:34 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/13 09:13:06 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/prompt.h"

static void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sig;
	sigaction(SIGINT, &sa, NULL);
}

static char	*get_line(void)
{
	char				*line;

	line = readline("\033[0;36mSea-Shell>\033[0m");
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
}

char	*prompt(struct termios *term)
{
	char			*line;

	tcgetattr(STDIN_FILENO, term);
	term->c_cc[VQUIT] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	handle_signal();
	line = get_line();
	tcgetattr(STDIN_FILENO, term);
	term->c_cc[VQUIT] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
	if (!line)
	{
		write(2, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	return (line);
}
