/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:31:10 by benji             #+#    #+#             */
/*   Updated: 2026/05/07 12:36:27 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_pipe(t_token *token)
{
	while(token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

t_tree	*parsing_main(t_token *token)
{
	t_tree	*tree;
	t_token	*first_token;

	if (!token)
		return (NULL);
	first_token = token;
	if (!have_pipe(token))
		return (make_right_part(token));
	tree = create_tree(first_token);
	if (!tree)
		return (NULL);
	tree = fill_right_part(tree);
	return (tree);
}
