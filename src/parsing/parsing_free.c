/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 14:09:45 by benji             #+#    #+#             */
/*   Updated: 2026/06/08 12:31:47 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_the_redirs(t_redir *redir)
{
	if (redir->next)
		free_the_redirs(redir->next);
	if (redir->file)
		free(redir->file);
	free(redir);
}

void	free_the_right_part(t_tree *tree)
{
	int	i;

	i = 0;
	while (tree->argv[i])
		free(tree->argv[i++]);
	free (tree->argv);
	if (tree->redirections)
		free_the_redirs(tree->redirections);
	free(tree);
}

void	free_rec(t_tree *tree)
{
	if (tree->left)
		free_rec(tree->left);
	if (tree->right)
		free_the_right_part(tree->right);
}

void	free_pipes(t_tree *tree)
{
	if (tree->left)
		free_pipes(tree->left);
	free(tree);
}

void	free_the_tree(t_tree *tree, int has_pipe)
{
	if (!has_pipe)
		return (free_the_right_part(tree));
	free_rec(tree);
	free_pipes(tree);
}
