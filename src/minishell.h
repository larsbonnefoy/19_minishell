/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:08:25 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/20 20:39:00 by hdelmas          ###   ########.fr       */
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

void	lexer_to_expander(t_lexer *lexer, t_env **env);

#endif