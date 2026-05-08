/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_right_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:17:08 by bribot            #+#    #+#             */
/*   Updated: 2026/05/08 10:11:00 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_segment_in_av(t_segment *seg)
{
	char *to_return;
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

t_tree	*make_right_part(t_token *token)
{
	t_tree	*to_return;
	int		size_av;
	int		i;

	i = 0;
	to_return = malloc(sizeof(t_tree));
	if (!to_return)
		return (NULL);
	size_av = get_size_of_tokens(token);
	to_return->argv = malloc (sizeof(char *) * (size_av + 1));
	if (!to_return->argv)
		return (NULL);
	while (i < size_av && token)
	{
		token = expand_tokens(token);
		if (token->segment && token->segment->value)
			to_return->argv[i] = put_segment_in_av(token->segment);
		if (!to_return->argv[i])
				return (NULL);
		token = token->next;
		i++;
	}
	to_return = set_value_to_null(to_return, i);
	to_return = handle_redirs_etc_parsing(to_return, token);
	return (to_return);
}

t_tree	*put_right_part(t_tree *tree)
{
	t_tree	*trot;
	t_tree	*tmp;

	tmp = malloc(sizeof(t_tree));
	if (!tmp)
		return (NULL);
	tree->right = tmp;
	tmp = make_right_part(tree->token_ref);
	return (tmp);
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
