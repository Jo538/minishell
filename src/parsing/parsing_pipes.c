/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:21:11 by bribot            #+#    #+#             */
/*   Updated: 2026/06/10 17:19:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*put_pipe_in_tree(t_tree *tree, t_token *token)
{
	t_tree	*created;
	t_tree	*trot;

	if (!tree)
		return (NULL);
	trot = tree;
	while (trot->left)
		trot = trot->left;
	created = malloc(sizeof(t_tree));
	if (!created)
		return (NULL);
	created->token_ref = token;
	created->type = PIPE;
	created->left = NULL;
	created->right = NULL;
	trot->left = created;
	return (tree);
}

t_tree	*pipe_init_tree(t_token *token, int *exit_code)
{
	t_tree	*tree;

	if (!token)
		return (NULL);
	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (*exit_code = ERR_FATAL, NULL);
	tree->type = PIPE;
	tree->token_ref = token;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

t_tree	*create_pipe_part(t_token *token, int *exit_code)
{
	t_tree	*tree;
	t_token	*first_word;

	tree = pipe_init_tree(token, exit_code);
	if (*exit_code == ERR_FATAL)
		return (NULL);
	while (have_a_token_left(token))
	{
		token = go_to_pipe_left(token);
		if (!token)
			break ;
		tree = put_pipe_in_tree(tree, token);
		if (!tree)
			return (NULL);
	}
	first_word = token;
	first_word = gt_first_word(first_word);
	if (first_word)
	{
		tree = put_pipe_in_tree(tree, first_word);
		if (!tree)
			return (NULL);
	}
	return (tree);
}

t_token	*find_last_pipe(t_token *token)
{
	t_token	*last_finded;

	last_finded = NULL;
	while (token)
	{
		if (token->type == PIPE)
			last_finded = token;
		token = token->next;
	}
	return (last_finded);
}

t_tree	*create_tree(t_token *token, int *exit_code)
{
	t_token	*last_pipe;
	t_tree	*tree;

	last_pipe = find_last_pipe(token);
	if (!last_pipe)
	{
		tree = malloc(sizeof(t_tree));
		if (!tree)
			return (NULL);
		tree->type = CMD;
		tree->token_ref = token;
		tree->left = NULL;
		tree->right = NULL;
		return (tree);
	}
	tree = create_pipe_part(last_pipe, exit_code);
	if (!tree)
		return (NULL);
	return (tree);
}
