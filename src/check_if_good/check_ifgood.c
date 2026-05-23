/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ifgood.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:17:09 by benji             #+#    #+#             */
/*   Updated: 2026/05/22 14:15:29 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return 1 si c est pas bon et 0 si c est

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
	int	i;
	
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
	while(token->next)
		token = token->next;
	if (token->type != WORD)
		return (1);
	return (0);
}

int	check_ifgood(t_token *token) //LA REGLE C EST RETOURNE 1 SI ERREUR | 0 SI GOOD
{
	if (check_pipes(token))
		return (1);
	if (check_redirs(token))
		return (1);
	return (0);
}
