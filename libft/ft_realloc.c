/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:22:06 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/21 10:29:41 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *p, size_t size_of, size_t size)
{
	void	*res;

	res = ft_malloc(size_of * (size + 1));
	if (!p)
		return (res);
	ft_bzero(res, size);
	ft_memmove(res, p, size -1);
	free(p);
	return (res);