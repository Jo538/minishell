/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orchestrator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:47:32 by admin             #+#    #+#             */
/*   Updated: 2026/04/22 13:04:38 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer_orchestrator(char *prompt, t_error *err)
{
	int		i;
	int		flag;
	t_state	state[2];
	t_token	*key_items[3];

	while (prompt[i])
	{
		state[CURRENT_STATE] = create_current_state(prompt[i], i, state[PREVIOUS_STATE]);
		flag = check_new_token(*previous_state, *current_state);
		if (flag == 0)
			segment_orchestrator(*previous_state, *current_state, last segment of last token, err);
		if (flag == 1)
			last_token = create_token(current_state, last_token, err);
		if (flag == 2)
			change_token_type(current_state, last_token, err);
		if (*err)
		{
				free_all(token_list);
				return NULL;
		}
	}
}
