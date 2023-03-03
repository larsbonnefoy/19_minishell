/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_in_order.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:59:19 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/03 13:19:39 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_export.h"

static int	*create_order(char **env, int size)
{
	int		*array;
	char	*last_name;
	char	*name;
	int		i;
	int		j;

	array = ft_calloc_exit(size, sizeof(int));
	i = -1;
	while (env[++i])
	{
		j = -1;
		last_name = getname(env[i]);
		while (env[++j])
		{
			name = getname(env[j]);
			if ((ft_strncmp(last_name,
						name, ft_strlen(last_name))) > 0)
				array[i] += 1;
			free(name);
		}
		free(last_name);
	}
	return (array);
}

int	print_in_order(char **env)
{
	int		size;
	int		*array;
	int		i;
	int		j;

	if (!env)
		exit(EXIT_FAILURE);
	size = -1;
	while (env[++size])
		;
	array = create_order(env, size);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (j < size && i != array[++j])
			;
		ft_putendl_fd(env[j], 1);
	}
	free(array);
	return (0);
}
