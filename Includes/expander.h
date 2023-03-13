/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:51:12 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/11 01:12:35 by hdelmas          ###   ########.fr       */
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

void	cleaner(t_lexer **lexer, t_env **local_env);
char	*expander(char *str, int quote_type, t_env **local_env);
void	lexer_to_expander(t_lexer *lexer, t_env **env);
char	*no_quotes_handling(char *to_join, char **cleaned, t_lexer **lexer);
char	*dup_word(char *str, int *i);
char	*strdup_in_quotes(char *str, int *i, int quote_type);

#endif
