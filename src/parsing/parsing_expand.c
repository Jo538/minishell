/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:18:40 by benji             #+#    #+#             */
/*   Updated: 2026/05/11 18:16:38 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_ch(char *str)
{
	char	*to_return;

	to_return = getenv(str);//ICI PENSER A AJOUTER LE CAS DE $? et trouver ou gerer $$
	free(str);
	return (to_return);
}

char	*get_to_expand(char *str, int *to_i, int *to_start)
{
	int		i;
	int		j;
	int		start;

	char	*to_return;
	i = *(to_i);
	start = *(to_start);
	i++;
	j = i;
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	to_return = ft_substr(str, j, i - j);
	start = i;
	to_return = expand_ch(to_return);
	(*to_i) = i;
	(*to_start) = start;
	return (to_return);
}

char	*expand_segtrot(char *str)
{
	int		i;
	int		start;
	char	*sub;
	char	*expand;
	char	*to_return;

	i = 0;
	start = 0;
	to_return = malloc(1);
	if (!to_return)
		return (NULL);
	to_return[0] = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		sub = ft_substr(str, start, i - start);
		to_return = ft_strjoin(to_return, sub);
		if (str[i] == '$')
		{
			// printf("BEFORE i = %d start = %d\n", i, start);
			expand = get_to_expand(str, &i, &start);
			// printf("AFTER i = %d start = %d\n", i, start);
			to_return = ft_strjoin(to_return, expand);
			printf("to return = %s\n", to_return);
		}
		// i++;
	}
	// printf("END to return = %s\n", to_return);
	return (to_return);
}

t_token	*expand_tokens(t_token	*token)
{
	t_segment	*segtrot;

	if (token->type != WORD)
		return (token);
	segtrot = token->segment;
	while (segtrot)
	{
		if (segtrot->quote_type != S_QUOTED)
			segtrot->value = expand_segtrot(segtrot->value); //il y a encore le cas de $$ a gerer et d autres scases type $? (la ca ne gere que les cas ultras classiques)
		segtrot = segtrot->next;
	}
	return (token); //necessite a faire
}

