/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:36:19 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/12 11:52:55 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buffer;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		buffer = *lst;
		*lst = (*lst)->next;
		del(buffer->content);
		free(buffer);
	}
	lst = NULL;
}
