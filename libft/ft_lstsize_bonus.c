/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:54:54 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/14 15:55:10 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

int	ft_lstsize(t_list *lst)
{
	int		len;

	if (!lst)
		return (0);
	len = 0;
	while (lst != NULL)
	{
		++len;
		lst = lst->next;
	}
	return (len);
}
