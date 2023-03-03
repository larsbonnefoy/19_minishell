/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:11:17 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/03 16:12:12 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UNSET_H
# define FT_UNSET_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include "../../env/src/env.h"
# include "../ft_export/ft_export.h"
# include "../ft_env/ft_env.h"
# include "../../libft/libft.h"

int	ft_unset(char **av, t_env **l_env, char ***env);

#endif