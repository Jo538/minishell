/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:31:10 by benji             #+#    #+#             */
/*   Updated: 2026/06/03 13:19:01 by bribot           ###   ########.fr       */
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

t_tree	*parsing_main(t_token *token, t_env **my_env, int *exit_code)
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
