/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:40:14 by admin             #+#    #+#             */
/*   Updated: 2026/06/08 12:20:03 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_new_token(int i, t_state previous_state, t_state current_state)
{
	if (current_state.quoting == UNQUOTED)
	{
		if (current_state.char_type != ON_SPACE
			&& current_state.char_type != previous_state.char_type)
			return (1);
		if (current_state.char_type == ON_SPACE)
			return (3);
		if (current_state.repeat > 0 && current_state.repeat % 2 == 0)
			return (2);
		if (current_state.repeat > 0 && current_state.repeat % 2 == 1)
			return (1);
	}
	if (previous_state.quoting == UNQUOTED
		&& (current_state.quoting == D_QUOTED
			|| current_state.quoting == S_QUOTED))
	{
		if (previous_state.char_type == ON_SPACE
			|| previous_state.char_type == ON_OPERATOR)
			return (1);
	}
	if (i == 0)
		return (1);
	return (0);
}

static t_token_type	find_token_type(t_state current_state)
{
	if (current_state.quoting == UNQUOTED)
	{
		if (current_state.c == '|')
			return (PIPE);
		if (current_state.c == '<' && current_state.repeat > 0
			&& current_state.repeat % 2 == 0)
			return (HEREDOC);
		if (current_state.c == '<')
			return (IN_DIR);
		if (current_state.c == '>' && current_state.repeat > 0
			&& current_state.repeat % 2 == 0)
			return (APPEND_OUT_DIR);
		if (current_state.c == '>')
			return (OUT_DIR);
	}
	return (WORD);
}

static void	create_node(t_token *new_token, t_token *last_token)
{
	if (!last_token)
	{
		new_token->before = NULL;
		new_token->next = NULL;
		return ;
	}
	new_token->before = last_token;
	new_token->next = NULL;
	last_token->next = new_token;
}

static void	create_segment(t_state state, t_token *new_token, int *exit_code)
{
	new_token->segment = ft_calloc(1, sizeof(t_segment));
	if (!new_token->segment)
	{
		*exit_code = ERR_FATAL;
		return ;
	}
	if (state.c == '\'' || state.c == '"')
		new_token->segment->value = ft_calloc(1, 1);
	else
		new_token->segment->value = ft_calloc(1, 2);
	if (!new_token->segment->value)
	{
		free(new_token->segment);
		*exit_code = ERR_FATAL;
		return ;
	}
	new_token->segment->quote_type = state.quoting;
	if (state.c == '\'' || state.c == '"')
		return ;
	new_token->segment->value[0] = state.c;
	new_token->segment->next = NULL;
}

t_token	*create_token(t_state state, t_token *last_token, int *exit_code)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		*exit_code = ERR_FATAL;
		return (NULL);
	}
	create_node(new_token, last_token);
	new_token->type = find_token_type(state);
	create_segment(state, new_token, exit_code);
	if (*exit_code == ERR_FATAL)
	{
		free(new_token);
		return (NULL);
	}
	return (new_token);
}
