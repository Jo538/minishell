/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:05:02 by bribot            #+#    #+#             */
/*   Updated: 2026/06/11 11:20:02 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors_siv(char *str, int allocated, char *to_return)
{
	free(str);
	if (allocated)
		free(to_return);
}

char	*init_expand_segtrot(t_istartsub *is)
{
	t_istartsub	istmp;
	char		*to_return;

	istmp = *is;
	istmp.i = 0;
	istmp.start = 0;
	to_return = malloc(1);
	if (!to_return)
		return (NULL);
	to_return[0] = 0;
	*is = istmp;
	return (to_return);
}

char	*expand_join_ab(char *to_return, char *expand)
{
	char	*tmp;

	if (!to_return)
		return (NULL);
	tmp = to_return;
	to_return = ft_strjoin(to_return, expand);
	free(tmp);
	free(expand);
	if (!to_return)
		return (NULL);
	return (to_return);
}

char	*expand_segtrot_gtr(t_istartsub is, char *str, char *to_return)
{
	char	*tmp;

	is.sub = ft_substr(str, is.start, is.i - is.start);
	if (!is.sub)
		return (free(to_return), NULL);
	tmp = to_return;
	to_return = ft_strjoin(to_return, is.sub);
	free(tmp);
	free(is.sub);
	return (to_return);
}

int	expand_need_to_in(char *str, int i)
{
	if (str[i] && str[i] != '$' && str[i] != ' ' && str[i] != 34
		&& str[i] != 39)
		return (1);
	return (0);
}
