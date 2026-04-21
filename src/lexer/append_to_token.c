/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 19:33:16 by admin             #+#    #+#             */
/*   Updated: 2026/04/21 14:30:08 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_new_segment(t_state previous_state, t_state current_state)
{
	if (current_state.quoting != previous_state.quoting)
		return (1);
	return (0);
}

void	add_new_segment(t_state current_state, t_segment *segment, t_error *err)
{
	t_segment	*new_segment;
	
	new_segment = ft_calloc(1, sizeof(t_segment));
	if (!new_segment)
	{
		*err = ERR_MALLOC;
		return ;
	}
	while (segment->next)
		segment = segment->next;
	segment->next = new_segment;
	new_segment->next = NULL;
	new_segment->quote_type = current_state.quoting;
	if (current_state.c == '\'' || current_state.c == '"')
		new_segment->value = ft_calloc(1, 1);
	else
		new_segment->value = ft_calloc(1, 2);
	if (!new_segment->value)
	{
		free(new_segment);
		*err = ERR_MALLOC;
		return ;
	}
	if (current_state.c == '\'' || current_state.c == '"')
		return ;
	segment->value[0] = current_state.c;
}

void	append_to_segment(t_state current_state, t_segment *segment, t_error *err)
{
	int		len;
	char	*new_value;
	
	len = ft_strlen(segment->value);
	new_value = ft_calloc(1, len + 2);
	if (!new_value)
	{
		*err = ERR_MALLOC;
		return ;
	}
	ft_strlcpy(new_value, segment->value, len + 2);
	new_value[len] = current_state.c;
	while (segment->next)
		segment = segment->next;
	free(segment->value);
	segment->value = new_value;
}

void	change_token_type(t_state current_state, t_token *last_token, t_error *err)
{
		if (current_state.c == '<')
			last_token->type = HEREDOC;
		else
			last_token->type = APPEND_OUT_DIR;
		append_to_segment(current_state, last_token->segment, err);
}
