/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:40:14 by admin             #+#    #+#             */
/*   Updated: 2026/04/19 23:41:17 by admin            ###   ########.fr       */
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
	}
	return (0);
}

t_token_type	find_token_type(t_state current_state)
{
	if (current_state.quoting == UNQUOTED)
	{
		if (current_state.c == '|')
			return (PIPE);
		if (current_state.c == '<' && current_state.repeat % 2 == 0)
			return (HEREDOC);
		if (current_state.c == '<')
			return (IN_DIR);
		if (current_state.c == '>' && current_state.repeat % 2 == 0)
			return (APPEND_OUT_DIR);
		if (current_state.c == '>')
			return (OUT_DIR);
	}
	return (WORD);
}

t_token	*create_first_token(t_state current_state, t_error *err)
{
	t_token	*head;
	t_token	*tail;

	head = ft_calloc(1, sizeof (t_token));
	if (!head)
	{
		*err = ERR_MALLOC;
		return (NULL);
	}
	head->before = NULL;
	head->next = NULL;
	head->type = find_token_type(current_state);
	head->segments = create_segment();
	return (head);
}

t_token	*create_token(t_state current_state, t_token *tail, t_error *err)
{
	t_token	*new_tail;

	new_tail = ft_calloc(1, sizeof (t_token));
	if (!new_tail)
	{
		*err = ERR_MALLOC;
		return (NULL);
	}
	new_tail->before = tail;
	new_tail->next = NULL;
	new_tail->type = find_token_type(current_state);
	new_tail->segments = create_segment();
	return (new_tail);
}
