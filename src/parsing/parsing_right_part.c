/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_right_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:17:08 by bribot            #+#    #+#             */
/*   Updated: 2026/06/05 12:54:27 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	free_right_part_tree(t_tree *tree, int arg_count)
// {
// 	while (arg_count > 0)
// 	{
// 		free(tree->argv[--arg_count]);
// 	}
// 	free(tree->argv);
// 	free(tree);
// }

// static int	count_arguments(t_token *token)
// {
// 	int	count;

// 	count = 0;
// 	if (!token)
// 		return (0);
// 	if (token->type == PIPE)
// 		token = token->next;
// 	while (token && token->type != PIPE)
// 	{
// 		if (token->type == WORD)
// 			count++;
// 		else
// 		{
// 			if (token->next)
// 				token = token->next;
// 		}
// 		if (token)
// 			token = token->next;
// 	}
// 	return (count);
// }

t_tree	*make_right_part(t_token *token, t_env **my_env, int *exit_code)
{
	t_tree	*tree;
	int		arg_count;

	if (token->type == PIPE)
		token = token->next;
	tree = init_tree_w_malloc(token);
	if (!tree)
		return(*exit_code = ERR_FATAL, NULL);
	tree = fill_av(tree, my_env, exit_code);
	if (!tree->argv)
		return(free(tree), *exit_code = ERR_FATAL, NULL);
	arg_count = 0;
	while (tree->argv[arg_count])
		arg_count++;
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
		{
			tree = handle_redirs(tree, my_env, exit_code);
		}
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
