/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:51:12 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/16 22:29:23 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H 
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include "../src/libft/libft.h"
# include "lexer.h"
# include "env.h"

# define S_QUOTE 39
# define D_QUOTE 34

typedef struct s_prevhead
{
	t_lexer	*head;
	t_lexer	*prev;
	int		check;
}	t_prevhead;

void	cleaner(t_lexer **lexer, t_env **local_env, t_prevhead *ph);
char	*expander(char *str, int quote_type, t_env **local_env);
void	lexer_to_expander(t_lexer **lexer, t_env **env);
char	*no_quotes_handling(char *to_join, char **cleaned, t_lexer **lexer, t_prevhead *ph);
char	*dup_word(char *str, int *i);
char	*strdup_in_quotes(char *str, int *i, int quote_type);

#endif
