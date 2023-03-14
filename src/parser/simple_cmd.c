/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:37:38 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/14 11:22:12 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

static t_simple_cmds	*create_single_cmd(t_lexer **lexer, int n)
{
	t_simple_cmds	*res;
	int				i;

	if (!lexer)
		exit(EXIT_FAILURE);
	i = 0;
	res = ft_malloc(sizeof(t_simple_cmds));
	res->av = NULL;
	res->redirections = NULL;
	res->pid = -2;
	res->next = NULL;
	res->n = n;
	while (*lexer && (*lexer)->token != PIPE)
	{
		i = lexer_to_cmd(lexer, res, i);
		if (*lexer)
			*lexer = (*lexer)->next;
	}
	return (res);
}

static void	simple_cmd_addback(t_simple_cmds **list, t_simple_cmds *new)
{
	t_simple_cmds	*tmp;

	if (!list || !new)
		exit(EXIT_FAILURE);
	tmp = *list;
	if (!*list)
		*list = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}	

t_simple_cmds	*create_simple_cmds(t_lexer *lexer)
{
	t_simple_cmds	*res;
	t_lexer			*head;
	t_simple_cmds	*cmd;
	int				n;

	head = lexer;
	res = NULL;
	n = 0;
	while (lexer)
	{
		cmd = create_single_cmd(&lexer, n);
		simple_cmd_addback(&res, cmd);
		if (lexer && lexer->token == PIPE)
		{
			n++;
			lexer = lexer->next;
		}
	}
	lexer = head;
	return (res);
}

void	destroy_simple_cmds(t_simple_cmds *cmd)
{
	int				i;
	t_simple_cmds	*tmp;

	while (cmd)
	{	
		i = -1;
		while (cmd->av && cmd->av[++i])
			free(cmd->av[i]);
		if (cmd->av)
			free(cmd->av);
		lexer_clear_list(&cmd->redirections);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}
