/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 14:15:46 by benji             #+#    #+#             */
/*   Updated: 2026/05/23 02:30:58 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_doubles_and_pipes_redirs(t_token *token)
{
	while (token)
	{
		if (token->type != WORD && token->type != PIPE)
		{
			if (!token->next || token->next->type != WORD)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	check_redirs(t_token *token)
{
	if (check_doubles_and_pipes_redirs(token))
		return (1);
	return (0);
}