/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_part_utils_redirs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:40:20 by benji             #+#    #+#             */
/*   Updated: 2026/06/10 17:40:36 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_segments(t_token *token, t_env **my_env, int *exit_code);

int	is_redirection_token(int type)
{
	if (type != PIPE)
		return (1);
	return (0);
}

t_tree	*create_fredir(t_tree *tree, t_env **my_env, int *exit_code)
{
	t_redir	*trot;
	char	*filename;

	if (!tree || !tree->token_ref
		|| !is_redirection_token(tree->token_ref->type))
		return (tree);
	if (!tree->token_ref->next || !tree->token_ref->next->segment
		|| !tree->token_ref->next->segment->value)
		return (tree);
	trot = malloc(sizeof(t_redir));
	if (!trot)
		return (*exit_code = ERR_FATAL, NULL);
	trot->type = tree->token_ref->type;
	trot->next = NULL;
	tree->token_ref = tree->token_ref->next;
	filename = join_segments(tree->token_ref, my_env, exit_code);
	if (*exit_code == ERR_FATAL)
		return (free(trot), NULL);
	trot->file = filename;
	if (!trot->file)
		return (free(trot), *exit_code = ERR_FATAL, NULL);
	tree->redirections = trot;
	tree->token_ref = tree->token_ref->next;
	return (tree);
}

t_redir	*create_redir(t_tree *tree, t_env **my_env, int *exit_code)
{
	t_redir	*trot;
	char	*filename;

	if (!tree || !tree->token_ref
		|| !is_redirection_token(tree->token_ref->type))
		return (NULL);
	if (!tree->token_ref->next || !tree->token_ref->next->segment
		|| !tree->token_ref->next->segment->value)
		return (NULL);
	trot = malloc(sizeof(t_redir));
	if (!trot)
		return (*exit_code = ERR_FATAL, NULL);
	trot->type = tree->token_ref->type;
	trot->next = NULL;
	tree->token_ref = tree->token_ref->next;
	filename = join_segments(tree->token_ref, my_env, exit_code);
	if (*exit_code == ERR_FATAL)
		return (free(trot), NULL);
	trot->file = filename;
	if (!trot->file)
		return (free(trot), *exit_code = ERR_FATAL, NULL);
	tree->token_ref = tree->token_ref->next;
	return (trot);
}

t_tree	*handle_redirs(t_tree *tree, t_env **my_env, int *exit_code)
{
	t_redir	*stat;

	if (!tree || !tree->token_ref
		|| !is_redirection_token(tree->token_ref->type))
		return (tree);
	if (!tree->redirections)
	{
		tree = create_fredir(tree, my_env, exit_code);
		if (*exit_code == ERR_FATAL)
			return (NULL);
		return (tree);
	}
	stat = tree->redirections;
	while (tree->redirections->next)
		tree->redirections = tree->redirections->next;
	tree->redirections->next = create_redir(tree, my_env, exit_code);
	if (*exit_code == ERR_FATAL)
		return (free_the_redirs(tree->redirections), NULL);
	tree->redirections = stat;
	return (tree);
}
