/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:52:02 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/10 12:01:32 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char *get_line(void);
#endif
