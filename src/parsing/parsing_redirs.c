/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:16:10 by benji             #+#    #+#             */
/*   Updated: 2026/05/20 17:19:59 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*make_redir(t_token *token)
{
	t_redir	*redir;

	if (!token)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = token->type;
	redir->next = NULL;
	token = token->next;
	if (token && token->segment && token->segment->value)
		redir->file = ft_strdup(token->segment->value);
	else
		redir->file = ft_strdup(" "); //Le if else sert a rien, il sert juste a pas avoir de segfaults tant qu on a pas une fonction qui verifie si tout marche
	if (!redir->file)
		return (NULL);
	token = token->next;
	if (token && (token->type == IN_DIR || token->type == OUT_DIR))
	{
		redir->next = make_redir(token);
		if (!redir->next)
			return (NULL);
	}
	return (redir);
}

t_tree	*handle_redirs_etc_parsing(t_tree *to_return, t_token *token)
{
	if (token && (token->type == IN_DIR || token->type == OUT_DIR))
	{
		to_return->redirections = make_redir(token);
		if (!to_return->redirections)
			return (NULL);
	}
	return (to_return);
}