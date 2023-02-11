/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:23:33 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/10/12 11:52:18 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lsti;

	lsti = *lst;
	if (*lst)
	{
		while (lsti->next != NULL)
			lsti = lsti->next;
		lsti->next = new;
	}
	else
		*lst = new;
}
