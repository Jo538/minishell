/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:19:32 by bribot            #+#    #+#             */
/*   Updated: 2026/06/10 17:41:01 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*gt_first_word(t_token *first_word)
{
	while (first_word && first_word->before)
		first_word = first_word->before;
	while (first_word && first_word->type != WORD)
		first_word = first_word->next;
	return (first_word);
}
