/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:51:30 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/02 14:33:16 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../libft/libft.h"
# define TRUE 1
# define FASLE 0

typedef struct s_env
{
	char			*name;
	char			*value;
	int				export;
	struct s_env	*next;
}	t_env;

char	*ft_getenv(char *var_name, t_env **list);
t_env	**env_init(void);
t_env	*env_new(char *name, char *new_value, int export_value);
t_env	**env_to_list(char **env);
void	env_addfront(t_env *new_node, t_env **list);
void	env_free_node(t_env *node);
void	env_free_all_node(t_env **list);
void	free_char_env(char **env);
t_env	**env_to_list(char **env);
char	**list_to_env(t_env **l_env);
void	env_reassign(t_env *to_add, t_env **l_env);
char	*getname(char *str);
char	*getval(char *str);

#endif
