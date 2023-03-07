/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:30:21 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/06 16:56:46 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ECHO_H
# define FT_ECHO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../src/libft/libft.h"
# include "env.h"

int	ft_echo(char **av, char ***env, t_env **l_env);

#endif