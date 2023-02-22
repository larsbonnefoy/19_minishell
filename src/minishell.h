/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:08:25 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/22 14:25:56 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
# include "../env/src/env.h"
# include "../expander/src/expander.h"
# include "../lexer/src/lexer.h"
# include "../parser/src/parser.h"
# include "../executor/src/executor.h"

void	lexer_to_expander(t_lexer *lexer, t_env **env);

#endif
