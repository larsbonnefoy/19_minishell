/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:32:54 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/02 21:58:32 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *p, size_t size_of, size_t size)
{
	void	*res;

	res = ft_malloc(size_of * (size));
	if (!p)
		return (res);
	ft_bzero(res, size_of * (size));
	ft_memmove(res, p, (size - 1) * size_of);
	free(p);
	return (res);
}
