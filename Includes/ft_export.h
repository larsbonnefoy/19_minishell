/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:50:41 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/09 14:06:16 by hdelmas          ###   ########.fr       */
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

int	is_export(char *str);
int	print_in_order(t_env **l_env);
int	add_exports_to_list(char **av, t_env **l_env, int export);

#endif