/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:09:19 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/11 16:11:29 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_malloc(size_t bytes)
{
	void	*mem;

	mem = malloc(bytes);
	if (!mem)
		exit(EXIT_FAILURE);
	return (mem);
}
