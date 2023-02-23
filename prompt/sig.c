/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:18:44 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/23 16:53:16 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*signal, sigaction, sigemptyset, sigaddset, kill,*/

#include "prompt.h"

int signal_init(void)
{
	sigset_t	set;
	
	sigemptyset(&set);	
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	return (0);
}