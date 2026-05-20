/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_part_utils_redirs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:40:20 by benji             #+#    #+#             */
/*   Updated: 2026/05/20 18:47:02 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_token(int type)
{
	if (type != PIPE)
		return (1);
	return (0);
}

t_tree	*create_fredir(t_tree *tree)
{
	t_redir	*trot;

	if (!tree || !tree->token_ref || !is_redirection_token(tree->token_ref->type))
		return (tree);
	if (!tree->token_ref->next || !tree->token_ref->next->segment || !tree->token_ref->next->segment->value)
		return (tree);
	trot = malloc(sizeof(t_redir));
	if (!trot)
		return (NULL);
	trot->type = tree->token_ref->type;
	trot->next = NULL;
	tree->token_ref = tree->token_ref->next;
	trot->file = ft_strdup(tree->token_ref->segment->value);
	if (!trot->file)
	{
		free(trot);
		return (NULL);
	}
	tree->redirections = trot;
	tree->token_ref = tree->token_ref->next;
	return (tree);
}

t_redir	*create_redir(t_tree *tree)
{
	t_redir	*trot;

	if (!tree || !tree->token_ref || !is_redirection_token(tree->token_ref->type))
		return (NULL);
	if (!tree->token_ref->next || !tree->token_ref->next->segment || !tree->token_ref->next->segment->value)
		return (NULL);
	trot = malloc(sizeof(t_redir));
	if (!trot)
		return (NULL);
	trot->type = tree->token_ref->type;
	trot->next = NULL;
	tree->token_ref = tree->token_ref->next;
	trot->file = ft_strdup(tree->token_ref->segment->value);
	if (!trot->file)
	{
		free(trot);
		return (NULL);
	}
	tree->token_ref = tree->token_ref->next;
	return (trot);
}

t_tree	*handle_redirs(t_tree *tree)
{
	t_redir	*stat;

	if (!tree || !tree->token_ref || !is_redirection_token(tree->token_ref->type))
		return (tree);

	if (!tree->redirections)
	{
		tree = create_fredir(tree);
		// if (!tree->redirections)
		// 	return (free_tree(tree), NULL);
		return (tree);
	}
	stat = tree->redirections;
	while (tree->redirections->next)
		tree->redirections = tree->redirections->next;
	tree->redirections->next = create_redir(tree);
	tree->redirections = stat;
	return (tree);
}