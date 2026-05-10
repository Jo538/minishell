/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:18:40 by benji             #+#    #+#             */
/*   Updated: 2026/05/05 15:25:53 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_segtrot(char *str)
{
	char	*to_return;

	to_return = getenv(&str[1]);
	free(str);
	return (to_return);
}

int	start_dol(char *str)
{
	if(str[0] == '$')
		return (1);
	return (0);
}

t_token	*expand_tokens(t_token	*token)
{
	t_segment	*segtrot;

	if (token->type != WORD)
		return (token);
	segtrot = token->segment;
	while (segtrot)
	{
		if (segtrot->quote_type != S_QUOTED  && start_dol(segtrot->value))
			segtrot->value = expand_segtrot(segtrot->value); //il y a encore le cas de $$ a gerer et d autres scases type $? (la ca ne gere que les cas ultras classiques)
		segtrot = segtrot->next;
	}
	return (token); //necessite a faire
}

