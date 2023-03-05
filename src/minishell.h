/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:08:25 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/05 14:48:28 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "../env/src/env.h"
# include "../expander/src/expander.h"
# include "../lexer/src/lexer.h"
# include "../parser/src/parser.h"
# include "../prompt/prompt.h"
# include "../executor/src/executor.h"
# include "../builtins/ft_echo/ft_echo.h"
# include "../builtins/ft_env/ft_env.h"
# include "../builtins/ft_exit/ft_exit.h"
# include "../builtins/ft_export/ft_export.h"
# include "../builtins/ft_pwd/ft_pwd.h"
# include "../builtins/ft_unset/ft_unset.h"

void	lexer_to_expander(t_lexer *lexer, t_env **env);

#endif