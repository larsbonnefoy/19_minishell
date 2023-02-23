/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:07:34 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/23 17:13:54 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,*/

#include "prompt.h"

char	*get_line(void)
{
	char	*line;
	
	// signal_init();88
	rl_on_new_line();
	line = readline("\033[0;36mSea-Shell>\033[0m");
	printf("[%s], [%zu]\n",line, ft_strlen(line));
	if (ft_strlen(line) > 0)
		add_history(line);
	// rl_replace_line("", 0);
	return (line);
}
