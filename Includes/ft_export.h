/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:50:41 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/05 19:22:46 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EXPORT_H
# define FT_EXPORT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include "env.h"
# include "ft_env.h"
# include "../src/libft/libft.h"

int	ft_export(char **av, t_env **l_env, char ***env);
int	is_export(char *str);
int	print_in_order(char **env);
#endif