/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ifgood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:17:09 by benji             #+#    #+#             */
/*   Updated: 2026/05/13 15:53:21 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return 1 si c est pas bon et 0 si c est

int	last_token_isnt_word(t_token *token)
{
	while(token->next)
		token = token->next;
	if (token->type != WORD)
		return (1);
	return (0);
}

int	check_ifgood(t_token *token)
{
	if (token->type != WORD || last_token_isnt_word(token))
		return (1);
	while (token)
	{
		if (token->type != WORD)
		{
			if (!token->before || !token->next || token->before->type != WORD || token->next->type != WORD)
				return (1);
		}
		token = token->next;
	}
	return (0);
}