/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_right_part_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 13:52:06 by benji             #+#    #+#             */
/*   Updated: 2026/06/03 15:37:15 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arguments(t_token *token)
{
	int	to_return;

	to_return = 0;
	while (token && token->type == WORD)
	{
		token = token->next;
		to_return++;
	}
	return (to_return);
}

char	*join_segments(t_token *token, t_env **my_env, int *exit_code)
{
	char		*to_return;
	char		*tmp;
	t_segment	*seg;

	if (!token)
		return (NULL);
	token = expand_tokens(token, my_env, exit_code);
	seg = token->segment;
	to_return = malloc(1);
	if (!to_return)
		return (*exit_code = ERR_FATAL, NULL);
	to_return[0] = 0;
	while (seg)
	{
		tmp = to_return;
		to_return = ft_strjoin(tmp, seg->value);
		free(tmp);
		if (!to_return)
			return (*exit_code = ERR_FATAL, NULL);
		seg = seg->next;
	}
	return (to_return);
}

void	free_argv(t_tree *tree, int i)
{
	while (i >= 0)
	{
		free(tree->argv[i]);
		i--;
	}
}

t_tree	*fill_av(t_tree *tree, t_env **my_env, int *exit_code)
{
	int		i;

	i = 0;
	while (tree->token_ref && tree->token_ref->type == WORD)
	{
		tree->argv[i] = join_segments(tree->token_ref, my_env, exit_code);
		if (!tree->argv[i])
			return (free_argv(tree, i), *exit_code = ERR_FATAL, NULL);
		i++;
		tree->token_ref = tree->token_ref->next;
	}
	tree->argv[i] = 0;
	return (tree);
}

t_tree	*init_tree_w_malloc(t_token *token)
{
	t_tree	*to_return;
	int		count;

	to_return = malloc(sizeof(t_tree));
	if (!to_return)
		return (NULL);
	if (token && token->type == PIPE)
		token = token->next;
	to_return->redirections = NULL;
	to_return->left = NULL;
	to_return->right = NULL;
	to_return->type = CMD;
	to_return->token_ref = token;
	count = count_arguments(token);
	to_return->argv = malloc(sizeof(char *) * (count + 1));
	if (!to_return->argv)
		return (free(to_return), NULL);
	return (to_return);
}
