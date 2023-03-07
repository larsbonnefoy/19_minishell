/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:56:24 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/06 15:57:06 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PWD_H
# define FT_PWD_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../src/libft/libft.h"
# include "env.h"

int	ft_pwd(char **av, char ***env, t_env **l_env);

#endif