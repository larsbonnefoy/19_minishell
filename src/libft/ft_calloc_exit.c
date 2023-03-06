/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:40:46 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/14 11:40:52 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc_exit(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_malloc(size * count);
	ft_bzero(ptr, size * count);
	return (ptr);
}
