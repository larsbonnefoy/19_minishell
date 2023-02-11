/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 14:43:01 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/11 16:04:54 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# include<stdlib.h>
# include<../libft/libft.h>

/*
	Ascii values of | < >
*/

typedef enum token
{
	PIPE = 124,
	GREATER = 62,
	LOWER = 60,

}	e_token;

typedef struct lexer
{
	char			*str;
	e_token			token;
	struct lexer 	*next;

}	t_lexer;

#endif
