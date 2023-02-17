/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smpcmd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:51:12 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/17 14:01:11 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SMPCMD_H
# define SMPCMD_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

# include "../../libft/libft.h"
# include "../../local_env/src/env.h"

# define S_QUOTE 39
# define D_QUOTE 34

char	*cleaner(char *str, t_env **local_env);
char	*expander(char *str, int quote_type, t_env **local_env);
#endif
