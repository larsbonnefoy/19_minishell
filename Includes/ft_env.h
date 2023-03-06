/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:15:04 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/06 16:56:26 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../src/libft/libft.h"
# include "env.h"

int	ft_env(char **av, char ***env, t_env **l_env);

#endif
