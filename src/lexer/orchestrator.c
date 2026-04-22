/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:47:32 by admin             #+#    #+#             */
/*   Updated: 2026/04/22 15:22:10 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	helper(int flag, t_state state[2], t_token *key_items[3], t_error *err)
{
	if (flag == 0)
		segment_orchestrator(state[PREVIOUS_STATE], state[CURRENT_STATE], key_items[LAST_SEGMENT], err);
	if (flag == 1)
		key_items[LAST_SEGMENT] = create_token(state[CURRENT_STATE], key_items[LAST_SEGMENT], err);
	if (flag == 2)
		change_token_type(state[CURRENT_STATE], key_items[LAST_SEGMENT], err);
}

t_token	*lexer_orchestrator(char *prompt, t_error *err)
{
	int		i;
	int		flag;
	t_state	state[2];
	t_token	*key_items[3];

	while (prompt[i])
	{
		state[CURRENT_STATE] = create_current_state(prompt[i], i, state[PREVIOUS_STATE]);
		flag = check_new_token(state[PREVIOUS_STATE], state[CURRENT_STATE]);
		helper(flag, state, key_items, err);
		if (*err)
		{
			free_all(key_items[FIRST_TOKEN]);
			return NULL;
		}
		i++;
	}
	return (key_items[FIRST_TOKEN]);
}
