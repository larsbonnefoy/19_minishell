/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:02:45 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/17 16:23:05 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/prompt.h"

void	handle_prompt(int sig)
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

void	handle_heredoc_child(int sig)
{
	if (sig == SIGINT)
	{
		g_ret_val = 130;
		ft_putchar_fd('\n', 1);
		exit(130);
	}
}

void	handle_heredoc_parent(int sig)
{
	if (sig == SIGINT)
		g_ret_val = 130;
}

void	handle_fork(int sig)
{
	if (sig == SIGINT)
		g_ret_val = 130;
	else if (sig == SIGQUIT)
		g_ret_val = 131;
	exit(g_ret_val);
}

void	handle_parent(int sig)
{
	if (sig == SIGINT)
	{	
		ft_putchar_fd('\n', 1);
		g_ret_val = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3", 1);
		ft_putchar_fd('\n', 1);
		g_ret_val = 131;
	}
}
