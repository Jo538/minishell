/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:40:14 by admin             #+#    #+#             */
/*   Updated: 2026/04/21 19:22:35 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_new_token(t_state previous_state, t_state current_state)
{
	if (current_state.quoting == UNQUOTED)
	{
		if (current_state.char_type != ON_SPACE
			&& current_state.char_type != previous_state.char_type)
			return (1);
		if (current_state.repeat > 0 && current_state.repeat % 2 == 0)
			return (2);
		if (current_state.repeat > 0 && current_state.repeat % 2 == 1)
			return (1);
	}
	return (0);
}

#ifdef TESTING
	t_token_type	find_token_type(t_state current_state)
#else
	static t_token_type	find_token_type(t_state current_state)
#endif
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

static void	create_node(t_token *new_token, t_token *tail)
{
	if (!tail)
	{
		new_token->before = NULL;
		new_token->next = NULL;
		return ;
	}
	new_token->before = tail;
	new_token->next = NULL;
	tail->next = new_token;
}

static void	create_segment(t_state current_state, t_token *new_token, t_error *err)
{
	new_token->segment = ft_calloc(1, sizeof(t_segment));
	if (!new_token->segment)
	{
		*err = ERR_MALLOC;
		return ;
	}
	if (current_state.c == '\'' || current_state.c == '"')
		new_token->segment->value = ft_calloc(1, 1);
	else
		new_token->segment->value = ft_calloc(1, 2);
	if (!new_token->segment->value)
	{
		free(new_token->segment);
		*err = ERR_MALLOC;
		return ;
	}
	if (current_state.c == '\'' || current_state.c == '"')
		return ;
	new_token->segment->value[0] = current_state.c;
	new_token->segment->quote_type = current_state.quoting;
	new_token->segment->next = NULL;
}

t_token	*create_token(t_state current_state, t_token *tail, t_error *err)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof (t_token));
	if (!new_token)
	{
		*err = ERR_MALLOC;
		return (NULL);
	}
	create_node(new_token, tail);
	new_token->type = find_token_type(current_state);
	create_segment(current_state, new_token, err);
	if (*err)
	{
		free(new_token);
		return (NULL);
	}
	return (new_token);
}
