/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:33:43 by hdelmas           #+#    #+#             */
/*   Updated: 2022/10/14 10:03:16 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		lst_len;
	t_list	*res;
	int		i;

	if (!lst)
		return (NULL);
	lst_len = ft_lstsize(lst);
	i = -1;
	res = lst;
	while (++i < lst_len - 1)
		res = res->next;
	return (res);
}
