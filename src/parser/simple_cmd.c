/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:37:38 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/13 17:32:03 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/parser.h"

static int	lexer_to_cmd(t_lexer **lexer, t_simple_cmds *res, int i)
{
	t_lexer			*tmp;

	if (!lexer)
		exit(EXIT_FAILURE);
	if ((*lexer)->str && (*lexer)->token == NOT_A_TOKEN)
	{
		res->av = (char **)ft_realloc_tab((void *)res->av,
				(sizeof(char *) /** (i + 1)*/), i + 1);
		res->av[i] = ft_strdup((*lexer)->str);
		res->av[++i] = NULL;
	}
	else if ((*lexer)->token != D_LOWER)
	{
		tmp = lexer_new_node(NULL, (*lexer)->token);
		lexer_add_back(&res->redirections, tmp);
		*lexer = (*lexer)->next;
		if (!*lexer)
			return (i);
		if ((*lexer)->str)
			tmp->str = ft_strdup((*lexer)->str);
	}
	else
	{
		if (!*lexer)
			return (i);
		if ((*lexer)->str)
		{
			tmp = lexer_new_node(ft_strdup((*lexer)->str), (*lexer)->token);
			tmp->hdoc_exp = (*lexer)->hdoc_exp;
			lexer_add_back(&res->redirections, tmp);
		}
	}
	return (i);
}

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
