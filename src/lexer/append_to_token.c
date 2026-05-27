/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 19:33:16 by admin             #+#    #+#             */
/*   Updated: 2026/05/27 15:26:33 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_new_segment(t_state prev, t_state cur)
{
	if (cur.quoting != prev.quoting)
	{
		if (prev.quoting == UNQUOTED
			&& (cur.quoting == D_QUOTED || cur.quoting == S_QUOTED)
			&& (prev.c == '\'' || prev.c == '"'))
			return (2);
		return (1);
	}
	return (0);
}

static t_segment	*add_new_segment(t_state cur, t_segment *last,
		int *exit_code)
{
	t_segment	*new_segment;

	new_segment = ft_calloc(1, sizeof(t_segment));
	if (!new_segment)
		return (*exit_code = ERR_FATAL, NULL);
	last->next = new_segment;
	new_segment->next = NULL;
	new_segment->quote_type = cur.quoting;
	if (cur.c == '\'' || cur.c == '"')
		new_segment->value = ft_calloc(1, 1);
	else
		new_segment->value = ft_calloc(1, 2);
	if (!new_segment->value)
		return (free(new_segment), *exit_code = ERR_FATAL, NULL);
	if (cur.c == '\'' || cur.c == '"')
		return (new_segment);
	new_segment->value[0] = cur.c;
	return (new_segment);
}

static void	append_to_segment(t_state cur, t_segment *last,
		int *exit_code)
{
	int		len;
	char	*new_value;

	len = ft_strlen(last->value);
	new_value = ft_calloc(1, len + 2);
	if (!new_value)
	{
		*exit_code = ERR_FATAL;
		return ;
	}
	ft_strlcpy(new_value, last->value, len + 2);
	new_value[len] = cur.c;
	free(last->value);
	last->value = new_value;
}

t_segment	*segment_orchestrator(t_state prev, t_state cur,
	t_segment *last, int *exit_code)
{
	int	flag;

	flag = check_new_segment(prev, cur);
	if (flag == 0)
		append_to_segment(cur, last, exit_code);
	if (flag == 1)
		last = add_new_segment(cur, last, exit_code);
	if (flag == 2)
		last->quote_type = cur.quoting;
	return (last);
}

void	change_token_type(t_state cur, t_token *last_token, t_error *err)
{
	if (cur.c == '<')
		last_token->type = HEREDOC;
	else
		last_token->type = APPEND_OUT_DIR;
	append_to_segment(cur, last_token->segment, err);
}
