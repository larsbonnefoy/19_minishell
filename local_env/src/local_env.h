/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:51:30 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/15 10:30:26 by hdelmas          ###   ########.fr       */
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
t_local	**local_env_init(void);
t_local	*local_new(char *name, char *new_value);
void	local_addfront(t_local *new_node, t_local **list);
void	local_free_node(t_local *node);
void	local_free_all_node(t_local **list);
#endif
