/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ifgood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:17:09 by benji             #+#    #+#             */
/*   Updated: 2026/06/03 18:40:04 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredocs(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == HEREDOC)
			i++;
		token = token->next;
	}
	if (i >= 16)
		return (1);
	return (0);
}

int	is_one_pipe(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
			j++;
	}
	if (j != 1)
		return (1);
	return (0);
}

int	check_pipes(t_token *token)
{
	if (token->type == PIPE)
		return (1);
	while (token)
	{
		if (token->type == PIPE && (!token->next || token->next->type == PIPE))
			return (1);
		if (token->type == PIPE && is_one_pipe(token->segment->value))
			return (1);
		token = token->next;
	}
	return (0);
}

int	last_token_isnt_word(t_token *token)
{
	while (token->next)
		token = token->next;
	if (token->type != WORD)
		return (1);
	return (0);
}

int	check_ifgood(t_token *token)
{
	if (check_heredocs(token))
		return (1);
	if (check_pipes(token))
		return (1);
	if (check_redirs(token))
		return (1);
	return (0);
}
