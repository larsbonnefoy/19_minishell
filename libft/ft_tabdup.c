/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 12:57:43 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/03 12:58:23 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	int		i;
	char	**res;
	int		size;

	i = -1;
	size = -1;
	if (!tab)
		exit(EXIT_FAILURE);
	while (tab[++size])
		;
	res = ft_malloc(sizeof(char *) * size + 1);
	while (tab[++i])
		res[i] = ft_strdup(tab[i]);
	return (res);
}
