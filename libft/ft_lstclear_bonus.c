/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:59:27 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/19 15:08:50 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	if (!*lst)
	{
		free(*lst);
		lst = NULL;
		return ;
	}
	temp = *lst;
	*lst = temp->next;
	ft_lstdelone(temp, del);
	ft_lstclear(lst, del);
}
