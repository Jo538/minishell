/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:31:10 by benji             #+#    #+#             */
/*   Updated: 2026/05/04 20:25:59 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*parsing_main(t_token *token)
{
	t_tree	*tree;
	t_token	*first_token;

	if (!token)
		return (NULL);
	first_token = token;
	tree = create_tree(first_token);
	if (!tree)
		return (NULL);
	tree = fill_right_part(tree);
	return (tree);
}
