/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_right_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:17:08 by bribot            #+#    #+#             */
/*   Updated: 2026/04/23 14:21:07 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*make_right_part(t_token *token, t_tree *tree)
{
	t_tree	*to_return;
	t_token	*trot_token;
	int		size_av;
	int		i;

	i = -1;
	printf("YAHOUUUUUUUUUUU\n");
	to_return = malloc(sizeof(t_tree));
	if (!to_return)
		return (NULL);
	trot_token = token->next;
	size_av = get_size_of_tokens(token);
	printf("%d\n", size_av);
	to_return->argv = malloc (size_av + 1);
	to_return->argv[size_av] = NULL;
	printf("test\n");
	if (!to_return->argv)
		return (NULL);
	while (++i < size_av)
	{
		to_return->argv[i] = strdup(token->segment->value); //remplacer par ft
		printf("CE QUI EST PRINT EST %d ICI %s", i, to_return->argv[i]);
		token = token->next;
	}
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
	tmp = make_right_part(tree->token_ref, tmp);
	return (tmp);
}

t_tree	*fill_right_part(t_tree *tree)
{
	t_tree	*trot;

	trot = tree;
	while (trot)
	{
		trot = put_right_part(trot);
		if (!trot)
			return (NULL);
		trot = trot->left;
	}
	return (tree);
}
