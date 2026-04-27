/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:05:50 by admin             #+#    #+#             */
/*   Updated: 2026/04/22 12:48:32 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_quoting	find_quoting(char c, int i, t_state previous_state)
{
	if (i == 0 && c == '\'')
		return (S_QUOTED);
	if (i == 0 && c == '\"')
		return (D_QUOTED);
	if (i == 0)
		return (UNQUOTED);
	if (previous_state.quoting == UNQUOTED && c == '\'')
		return (S_QUOTED);
	if (previous_state.quoting == S_QUOTED && c != '\'')
		return (S_QUOTED);
	if (previous_state.quoting == UNQUOTED && c == '\"')
		return (D_QUOTED);
	if (previous_state.quoting == D_QUOTED && c != '\"')
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

int	find_repeat(char c, int i, t_state previous_state, t_quoting quote_type)
{
	if (quote_type == UNQUOTED)
	{
		if (i == 0 && (c == '<' || c == '>'))
			return (1);
		if (i == 0)
			return (0);
		if (previous_state.c == '<' && c == '<')
			return (previous_state.repeat + 1);
		if (previous_state.c == '>' && c == '>')
			return (previous_state.repeat + 1);
		if (c == '<' || c == '>')
			return (1);		
	}
	return (0);
}

t_state	create_current_state(char c, int i, t_state previous_state)
{
	t_state	current_state;

	current_state.c = c;
	current_state.quoting = find_quoting(c, i, previous_state);
	current_state.char_type = find_char_type(c, current_state.quoting);
	current_state.repeat = find_repeat(c, i, previous_state, current_state.quoting);
	return (current_state);
}
