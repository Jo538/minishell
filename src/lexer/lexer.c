/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:05:50 by admin             #+#    #+#             */
/*   Updated: 2026/04/19 18:17:12 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_quoting	find_quoting(char c, t_state *previous_state)
{
	if (!previous_state && c == '\'')
		return (S_QUOTED);
	if (!previous_state && c == '\"')
		return (D_QUOTED);
	if (!previous_state)
		return (UNQUOTED);
	if (previous_state->quoting == UNQUOTED && c == '\'')
		return (S_QUOTED);
	if (previous_state->quoting == S_QUOTED && c != '\'')
		return (S_QUOTED);
	if (previous_state->quoting == UNQUOTED && c == '\"')
		return (D_QUOTED);
	if (previous_state->quoting == D_QUOTED && c != '\"')
		return (D_QUOTED);
	return (UNQUOTED);
}

t_char_type	find_char_type(char c, t_quoting quote_type)
{
	if (quote_type == UNQUOTED)
	{
		if (c == '<' || c == '>' || c == '|')
			return (ON_OPERATOR);
		if (c == ' ')
			return (ON_SPACE);
	}
	return (ON_WORD);
}

int	find_repeat(char c, t_state *previous_state, t_quoting quote_type)
{
	if (quote_type == UNQUOTED)
	{
		if (!previous_state && (c == '<' || c == '>'))
			return (1);
		if (!previous_state)
			return (0);
		if (previous_state->c == '<' && c == '<')
			return (++previous_state->repeat);
		if (previous_state->c == '>' && c == '>')
			return (++previous_state->repeat);
		if (c == '<' || c == '>')
			return (1);		
	}
	return (0);
}

t_state	*create_current_state(char c, t_state *previous_state, t_error *err)
{
	t_state	*current_state;

	current_state = ft_calloc(1, sizeof(t_state));
	if (!current_state)
	{
		*err = ERR_MALLOC;
		return (NULL);
	}	

	current_state->c = c;
	current_state->quoting = find_quoting(c, previous_state);
	current_state->char_type = find_char_type(c, current_state->quoting);
	current_state->repeat = find_repeat(c, previous_state, current_state->quoting);
	return (current_state);
}
