/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:07:46 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/17 11:12:59 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	handle_prompt(int sig);
void	handle_heredoc_child(int sig);
void	handle_heredoc_parent(int sig);
void	handle_fork(int sig);
void	handle_parent(int sig);

#endif