/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:40:47 by hdelmas           #+#    #+#             */
/*   Updated: 2023/02/17 09:41:28 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_ff(char *str1, char *str2)
{
	char	*res;

	if (!str1 || !str2)
		exit(EXIT_FAILURE);
	res = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (res);
}
