/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:51:39 by bribot            #+#    #+#             */
/*   Updated: 2026/04/30 15:46:38 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size_of_tokens(t_token *token)
{
	int	to_return;

	if (!token)
		return (0);
	to_return = 1;
	while (token && token->next && token->next->type == WORD)
	{
		to_return++;
		token = token->next;
	}
	return (to_return);
}

int	have_a_token_left(t_token *token)
{
	token = token->before;
	while (token)
	{
		if (token->type == WORD)
			return (1);
		token = token->before;
	}
	return (0);
}

t_token	*go_to_pipe_left(t_token *token)
{
	while (token)
	{
		token = token->before;
		if (!token)
			return (NULL);
		if (token->type == WORD)
			return (token);
	}
	return (NULL);
}
