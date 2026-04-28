/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:31:10 by benji             #+#    #+#             */
/*   Updated: 2026/04/27 18:36:26 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*parsing_main(t_token *token)
{
	t_tree	*tree;
	t_token	*first_token;

	first_token = token;
	tree = create_tree(first_token);
	tree = fill_right_part(tree);
	return (tree);
}
