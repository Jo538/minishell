/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:51:39 by bribot            #+#    #+#             */
/*   Updated: 2026/05/20 15:27:31 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_a_token_left(t_token *token)
{
	token = token->before;
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->before;
	}
	return (0);
}

t_token	*go_to_pipe_left(t_token *token)
{
	while (token)
	{
		token = token->before;
		if (!token)
			return (NULL);
		if (token->type == PIPE)
			return (token);
	}
	return (NULL);
}

// char	*join_segments(t_token *token)
// {
// 	char		*to_return;
// 	char		*tmp;
// 	t_segment	*seg;

// 	if (!token)
// 		return (NULL);
// 	token = expand_tokens(token);
// 	seg = token->segment;
// 	to_return = malloc(1);
// 	if (!to_return)
// 		return (NULL);
// 	to_return[0] = 0;
// 	while (seg)
// 	{
// 		tmp = to_return;
// 		to_return = ft_strjoin(tmp, seg->value);
// 		free(tmp);
// 		if (!to_return)
// 			return (NULL);
// 		seg = seg->next;
// 	}
// 	return (to_return);
// }
