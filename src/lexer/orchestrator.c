/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:47:32 by admin             #+#    #+#             */
/*   Updated: 2026/04/24 11:46:08 by admin            ###   ########.fr       */
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
	t_segment	*segment;


	while (token)
	{
		next_token = token->next;
		free_segment_list(token->segment);
		free(token);
		token = next_token;
	}
}

static void	helper(int flag, t_state state[2], t_key_items *key_items, t_error *err)
{
	if (flag == 0)
		key_items->last_segment = segment_orchestrator(state[PREVIOUS_STATE], state[CURRENT_STATE], key_items->last_segment, err);
	if (flag == 1)
		key_items->last_token = create_token(state[CURRENT_STATE], key_items->last_token, err);
	if (flag == 2)
		change_token_type(state[CURRENT_STATE], key_items->last_token, err);
}

t_token	*lexer_orchestrator(char *prompt, t_error *err)
{
	int			i;
	int			flag;
	t_state		state[2];
	t_key_items	key_items;

	while (prompt[i])
	{
		state[CURRENT_STATE] = create_current_state(prompt[i], i, state[PREVIOUS_STATE]);
		flag = check_new_token(state[PREVIOUS_STATE], state[CURRENT_STATE]);
		helper(flag, state, &key_items, err);
		if (*err)
		{
			free_token_list(key_items.first_token);
			return NULL;
		}
		i++;
	}
	return (key_items.first_token);
}
