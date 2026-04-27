/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 19:33:16 by admin             #+#    #+#             */
/*   Updated: 2026/04/27 00:46:43 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_new_segment(t_state previous_state, t_state current_state)
{
	if (current_state.quoting != previous_state.quoting)
	{
		if (previous_state.quoting == UNQUOTED 
			&& (current_state.quoting == D_QUOTED || current_state.quoting == S_QUOTED)
				&& (previous_state.c == '\'' || previous_state.c == '"'))
			return (2) ;
		return (1) ;
	}
	return (0);
}

#ifdef TESTING
	t_segment	*add_new_segment(t_state current_state, t_segment *last_segment, t_error *err)
#else
	static t_segment	*add_new_segment(t_state current_state, t_segment *last_segment, t_error *err)
#endif
{
	t_segment	*new_segment;
	
	new_segment = ft_calloc(1, sizeof(t_segment));
	if (!new_segment)
		return (*err = ERR_MALLOC, NULL);

	last_segment->next = new_segment;
	new_segment->next = NULL;
	new_segment->quote_type = current_state.quoting;

	if (current_state.c == '\'' || current_state.c == '"')
		new_segment->value = ft_calloc(1, 1);
	else
		new_segment->value = ft_calloc(1, 2);
	if (!new_segment->value)
		return (free(new_segment), *err = ERR_MALLOC, NULL);
	if (current_state.c == '\'' || current_state.c == '"')
		return (new_segment);
	new_segment->value[0] = current_state.c;
	return (new_segment);
}

#ifdef TESTING
	void	append_to_segment(t_state current_state, t_segment *last_segment, t_error *err)
#else
	static void	append_to_segment(t_state current_state, t_segment *last_segment, t_error *err)
#endif
{
	int		len;
	char	*new_value;
	
	len = ft_strlen(last_segment->value);
	new_value = ft_calloc(1, len + 2);
	if (!new_value)
	{
		*err = ERR_MALLOC;
		return ;
	}
	ft_strlcpy(new_value, last_segment->value, len + 2);
	new_value[len] = current_state.c;
	free(last_segment->value);
	last_segment->value = new_value;
}

t_segment	*segment_orchestrator(t_state previous_state, t_state current_state, t_segment *last_segment, t_error *err)
{
	int	flag;

	flag = check_new_segment(previous_state, current_state);
	if (flag == 0)
		append_to_segment(current_state, last_segment, err);
	if (flag == 1)
		last_segment = add_new_segment(current_state, last_segment, err);
	if (flag == 2)
		last_segment->quote_type = current_state.quoting;
	return (last_segment);
}

void	change_token_type(t_state current_state, t_token *last_token, t_error *err)
{
		if (current_state.c == '<')
			last_token->type = HEREDOC;
		else
			last_token->type = APPEND_OUT_DIR;
		append_to_segment(current_state, last_token->segment, err);
}
