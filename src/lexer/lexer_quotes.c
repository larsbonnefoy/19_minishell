/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:39:40 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/13 13:34:44 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/lexer.h"

static	int	is_heredoc_del(int beg_sub, char *main_str);
static	char	*join_substr(char *main, char *clean, int beg_sub, int len);
static	int	remove_quotes(char *main_str, char *sub_str, int beg_sub);

/*
	Remove subsequent quotes that are not alone-standing 
		->if they are empty && direclty next to char != from space or ht
	Sends back every non-empty string enclosed by the same quotes
*/
char	*handle_sub_quotes(char *str)
{
	int		i;
	int		prev_i;
	int		beg_sub;
	char	*clean_str;

	i = 0;
	beg_sub = i;
	clean_str = ft_calloc_exit(1, sizeof(char));
	while (str[i])
	{
		prev_i = i;
		if (is_quote(str[i]))
		{
			i += find_quotes(str + i, str[i]);
			if (i == prev_i)
				return (NULL);
		}
		else
			while (str[i] != '\0' && !is_quote(str[i]))
				i++;
		clean_str = join_substr(str, clean_str, beg_sub, i - beg_sub);
		printf("clean_str = %s\n", clean_str);
		beg_sub = i;
	}
	return (clean_str);
}

/*
 *	Joins in clean_str chars from main_str[beg_sub; beg_sub_str + len] 
 */
static	char	*join_substr(char *main, char *clean_str, int beg_sub, int len)
{
	char	*sub_str;
	char	*new_clean_str;

	sub_str = ft_substr(main, beg_sub, len);
	if (sub_str == NULL)
		return (NULL);
	if (!(remove_quotes(main, sub_str, beg_sub)))
	{
		new_clean_str = ft_strjoin_ff(clean_str, sub_str);
		return (new_clean_str);
	}
	else
	{
		free(sub_str);
		return (clean_str);
	}
}

/*
 * Returns 1 the quotes have to removed
 * Else returns 0
 */
static	int	remove_quotes(char *main, char *sub_str, int beg_sub)
{
	int		len;
	char	elem_left;
	char	elem_right;

	if (is_heredoc_del(beg_sub, main))
		return (0);
	len = ft_strlen(sub_str);
	if (len != 2 || !(is_quote(sub_str[0]) && is_quote(sub_str[1])))
		return (0);
	elem_right = main[beg_sub + len];
	if (beg_sub != 0)
		elem_left = main[beg_sub -1];
	if (beg_sub == 0)
		if (is_space_or_ht(elem_right) || ft_strlen(main) == 2)
			return (0);
	if (main[beg_sub + len] == '\0')
		if (is_space_or_ht(elem_left) || elem_left == '$')
			return (0);
	if (is_space_or_ht(elem_left) && is_space_or_ht(elem_right))
		return (0);
	return (1);
}

static int	is_heredoc_del(int beg_sub, char *main)
{
	int	i;

	i = beg_sub - 1;
	while (ft_isalnum(main[i]) && i != 0 && main[i] != '<')
		i--;
	while (is_space_or_ht(main[i]) && i != 0)
		i--;
	if (i > 0)
	{
		if (main[i] == '<' && main[i - 1] == '<')
			return (1);
	}
	return (0);
}
