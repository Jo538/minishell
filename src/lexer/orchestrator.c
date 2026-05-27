/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:47:32 by admin             #+#    #+#             */
/*   Updated: 2026/05/27 15:20:39 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_segment_list(t_segment *segment)
{
	t_segment	*next_segment;

	while (segment)
	{
		next_segment = segment->next;
		free(segment->value);
		free(segment);
		segment = next_segment;
	}
}

void	free_token_list(t_token *token)
{
	t_token		*next_token;

	while (token)
	{
		next_token = token->next;
		free_segment_list(token->segment);
		free(token);
		token = next_token;
	}
}

static void	helper(int flag, t_state state[2], t_key_items *k, int *ec)
{
	if (flag == 0)
		k->last_segment = segment_orchestrator(state[PREVIOUS_STATE],
				state[CURRENT_STATE], k->last_segment, ec);
	if (flag == 1)
	{
		k->last_token = create_token(state[CURRENT_STATE],
				k->last_token, ec);
		k->last_segment = k->last_token->segment;
	}
	if (flag == 2)
		change_token_type(state[CURRENT_STATE], k->last_token, ec);
	if (!k->first_token)
		k->first_token = k->last_token;
	if (flag == 3)
		return ;
}

static int	is_unclosed_quote(t_state state)
{
	return (state.quoting == S_QUOTED || state.quoting == D_QUOTED);
}

t_token	*lexer(char *prompt, int *exit_code)
{
	int			i;
	int			len;
	t_state		state[2];
	t_key_items	k;

	i = 0;
	len = ft_strlen(prompt);
	ft_bzero(&k, sizeof(t_key_items));
	ft_bzero(state, 2 * sizeof(t_state));
	while (i < len)
	{
		state[CURRENT_STATE] = create_current_state(prompt[i], i,
				state[PREVIOUS_STATE]);
		helper(check_new_token(i, state[PREVIOUS_STATE],
				state[CURRENT_STATE]), state, &k, exit_code);
		if (*exit_code == ERR_FATAL)
			return (free_token_list(k.first_token), NULL);
		state[PREVIOUS_STATE] = state[CURRENT_STATE];
		i++;
	}
	if (is_unclosed_quote(state[CURRENT_STATE]))
		return (ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2),
			free_token_list(k.first_token), *exit_code = ERR_SYNTAX, NULL);
	return (k.first_token);
}
