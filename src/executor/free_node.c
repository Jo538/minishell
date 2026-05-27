/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:27:25 by admin             #+#    #+#             */
/*   Updated: 2026/05/26 18:37:02 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirections(t_tree *node)
{
	t_redir	*tmp;

	tmp = node->redirections;
	while (node->redirections)
	{
		free(node->redirections->file);
		tmp = node->redirections->next;
		free(node->redirections);
		node->redirections = tmp;
	}
}

static void	free_argv(t_tree *node)
{
	int	i;

	i = 0;
	while (node->argv[i])
	{
		free(node->argv[i]);
		i++;
	}
	free(node->argv);
}

void	free_node(t_tree *node)
{
	if (node->type == CMD)
	{
		if (node->argv)
			free_argv(node);
		if (node->redirections)
			free_redirections(node);
	}
	if (node->left)
		free_node(node->left);
	if (node->right)
		free_node(node->right);
	free(node);
}

void	free_and_exit(t_tree *node, t_env **my_env, int *exit_code)
{
	free_node(node);
	free_my_env(my_env);
	exit(*exit_code);
}
