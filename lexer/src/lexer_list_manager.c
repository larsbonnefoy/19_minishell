/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:12:23 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/02/16 16:38:10 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*lexer_new_node(char *str, e_token token)
{
	t_lexer	*new_node;

	new_node = ft_malloc(sizeof(t_lexer));
	new_node->str = str;
	new_node->token = token;
	new_node->next = NULL;
	return (new_node);
}

void	lexer_add_back(t_lexer **lexer_list, t_lexer *new_node)
{
	t_lexer	*tmp;

	tmp = *lexer_list;
	if (*lexer_list)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	else
		*lexer_list = new_node;
}

void	lexer_print_list(t_lexer **lexer_list)
{
	t_lexer	*tmp;

	tmp = *lexer_list;
	while (tmp)
	{
		if (tmp->str)
			printf("[%s] [%d]\n", tmp->str, tmp->token);
		else
			printf("[null] [%d]\n", tmp->token);
		tmp = tmp->next;
	}
}

void	lexer_clear_list(t_lexer **lexer_list)
{
	t_lexer	*buffer;

	while (*lexer_list)
	{
		buffer = *lexer_list;
		*lexer_list = (*lexer_list)->next;
		free(buffer);
	}
}
