/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_right_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:17:08 by bribot            #+#    #+#             */
/*   Updated: 2026/06/10 17:39:10 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*start_tree(t_token *token, t_env **my_env, int *exit_code,
				int *arg_count)
{
	t_tree	*tree;
	int		i;

	i = 0;
	if (token->type == PIPE)
		token = token->next;
	tree = init_tree_w_malloc(token);
	if (!tree)
		return (*exit_code = ERR_FATAL, NULL);
	tree = fill_av(tree, my_env, exit_code);
	if (!tree->argv)
		return (free(tree), *exit_code = ERR_FATAL, NULL);
	i = 0;
	while (tree->argv[i])
		i++;
	*arg_count = i;
	return (tree);
}

t_tree	*make_right_part(t_token *token, t_env **my_env, int *exit_code)
{
	t_tree	*tree;
	int		arg_count;

	tree = start_tree(token, my_env, exit_code, &arg_count);
	if (!tree)
		return (*exit_code = ERR_FATAL, NULL);
	tree = handle_redirs(tree, my_env, exit_code);
	while (tree->token_ref && tree->token_ref->type != PIPE)
	{
		if (*exit_code == ERR_FATAL)
			return (NULL);
		if (tree->token_ref->type == WORD)
		{
			tree = fill_av_from_index(tree, &arg_count, my_env, exit_code);
			if (*exit_code == ERR_FATAL)
				return (NULL);
		}
		else
			tree = handle_redirs(tree, my_env, exit_code);
	}
	if (*exit_code == ERR_FATAL)
		return (NULL);
	return (tree);
}

t_tree	*fill_right_part(t_tree *tree, t_env **my_env, int *exit_code)
{
	t_tree	*trot;

	if (!tree)
		return (NULL);
	trot = tree;
	while (trot)
	{
		if (trot->type == PIPE || trot->type == CMD)
		{
			trot->right = make_right_part(trot->token_ref, my_env, exit_code);
			if (*exit_code == ERR_FATAL)
				return (NULL);
		}
		trot = trot->left;
	}
	return (tree);
}
