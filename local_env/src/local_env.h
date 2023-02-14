/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:51:30 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/14 18:35:55 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_ENV_H
# define LOCAL_ENV_H

# include "../../libft/libft.h"

typedef struct s_local
{
	char			*name;
	char			*value;
	struct s_local	*next;
}	t_local;

char	*ft_get_local_env(char *var_name, t_local **local);

#endif
