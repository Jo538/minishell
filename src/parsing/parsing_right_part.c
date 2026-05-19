/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_right_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:17:08 by bribot            #+#    #+#             */
/*   Updated: 2026/05/18 18:52:13 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_segment_in_av(t_segment *seg)
{
	char	*to_return;
	char	*tmp;

	to_return = malloc(1);
	if (!to_return)
		return (NULL);
	to_return[0] = 0;
	while (seg && seg->value)
	{
		tmp = to_return;
		to_return = ft_strjoin(tmp, seg->value);
		if (!to_return)
			return (NULL);
		free (tmp);
		seg = seg->next;
	}
	return (to_return);
}

t_tree	*set_value_to_null(t_tree *to_return, int i)
{
	to_return->argv[i] = NULL;
	to_return->left = NULL;
	to_return->right = NULL;
	to_return->type = CMD;
	return (to_return);
}

// t_tree	*make_right_part(t_token *token)
// {
// 	t_tree	*to_return;

// 	to_return = make_first_tree_node(to_return, token);
// 	if (!to_return)
// 		return(NULL);
// }

// t_tree	*make_right_part(t_token *token)
// {
// 	t_tree	*to_return;
// 	int		size_av;
// 	int		i;

// 	i = 0;
// 	to_return = malloc(sizeof(t_tree));
// 	if (!to_return)
// 		return (NULL);
// 	to_return->redirections = NULL;
// 	if (token->type == PIPE)
// 		token = token->next;
// 	size_av = get_size_of_tokens(token);
// 	to_return->argv = malloc (sizeof(char *) * (size_av + 1));
// 	if (!to_return->argv)
// 		return (NULL);
// 	while (i < size_av && token)
// 	{
// 		token = expand_tokens(token);
// 		if (token->segment && token->segment->value)
// 			to_return->argv[i] = put_segment_in_av(token->segment);
// 		if (!to_return->argv[i])
// 			return (NULL);
// 		token = token->next;
// 		i++; // si BGUL le mettre dans le if juste au dessus
// 	}
// 	to_return = set_value_to_null(to_return, i);
// 	to_return = handle_redirs_etc_parsing(to_return, token); //si besoin de gagner une ligne, mettre ca dans le return;
// 	return (to_return);
// }

// t_tree	*put_right_part(t_tree *tree)
// {
// 	t_tree	*trot;
// 	t_tree	*tmp;

// 	tmp = malloc(sizeof(t_tree));
// 	if (!tmp)
// 		return (NULL);
// 	tree->right = tmp;
// 	tmp = make_right_part(tree->token_ref);
// 	return (tmp);
// } // JE CROIS QUE CETTE FONCTION EST SUPPRIMABLE

t_tree	*handle_redirs(t_tree *tree, t_token *token)
{
	
	return (NULL);
}

t_tree	*handle_heredoc_etc(t_tree *tree, t_token *token)
{
	return (NULL);
}

t_tree	*malloc_tree(t_token *token)
{
	int		i;
	t_tree	*to_return;

	i = 0;
	while (token && token->type == WORD)
	{
		i++;
		token = token->next;
	}
	to_return->argv = malloc (sizeof(char *) * i + 1);
	if (!to_return->argv)
		return (NULL);
	to_return->argv[i] = 0;
	return (to_return);
}

t_tree	*handle_words(t_tree *tree, t_token **token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = (*token);
	// tmp = token;
	// while (token && token == WORD)
	// {
	// 	i++;
	// 	token = token->next;
	// }
	// tree->argv = malloc (sizeof(char *) * i + 1);
	// if (!tree->argv)
	// 	return (NULL);
	tree = malloc_tree(tmp);
	if (!tree)
		return (NULL);
	while (tree->argv[i])
	{
		tree->argv[i] = ft_strdup(join_segments(tmp));
		tmp = tmp->next;
		i++;
	}
	return (tree);
}

t_tree	*make_right_part(t_token *token)
{
	t_tree	*tree;

	// tree = malloc(sizeof(t_tree));
	// if (!tree);
	// 	return (NULL);
	// while (token && token->type != PIPE)
	// {
	// 	if (token->type == IN_DIR || token->type == OUT_DIR)
	// 		handle_redirs(tree, token);
	// 	if (token->type == HEREDOC || token->type == APPEND_OUT_DIR)
	// 		handle_heredoc_etc(tree, token);
	// 	if (token->type == WORD)
			tree = handle_words(tree, &token);
	// }
	return (tree);
}

t_tree	*fill_right_part(t_tree *tree)
{
	t_tree	*trot;

	if (!tree)
		return (NULL);
	trot = tree;
	while (trot)
	{
		if (trot->type == PIPE || trot->type == CMD)
		{
			trot->right = make_right_part(trot->token_ref);
			if (!trot->right)
				return (NULL);
		}
		trot = trot->left;
	}
	return (tree);
}
