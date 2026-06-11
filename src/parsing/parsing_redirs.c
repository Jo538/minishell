/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 16:16:10 by benji             #+#    #+#             */
/*   Updated: 2026/06/11 11:08:54 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_has_quotes(t_token *token)
{
	t_segment	*seg;

	if (!token)
		return (0);
	seg = token->segment;
	while (seg)
	{
		if (seg->quote_type != UNQUOTED)
			return (1);
		seg = seg->next;
	}
	return (0);
}

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
		redir->file = ft_strdup(" ");
	if (!redir->file)
		return (NULL);
	redir->heredoc_quoted = (redir->type == HEREDOC && token_has_quotes(token));
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
