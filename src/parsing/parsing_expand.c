/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:18:40 by benji             #+#    #+#             */
/*   Updated: 2026/06/10 16:19:15 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_in_env(char *str, t_env **my_env, int *exit)
{
	int		i;

	i = 0;
	if (str[0] == '?' || str[0] == ' ' || str[0] == '\0')
		return (spe_siv(str, exit));
	while (my_env[i])
	{
		if (ft_strlen(my_env[i]->key) == ft_strlen(str)
			&& !(ft_strncmp(my_env[i]->key, str, ft_strlen(str))))
		{
			if (my_env[i]->value && my_env[i]->value[0] != '\0')
				return (ft_strdup(my_env[i]->value));
			else
				return (ft_strdup(""));
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*expand_ch(char *str, t_env **my_env, int *exit_code)
{
	char	*to_return;
	char	*result;
	int		allocated;

	allocated = 0;
	to_return = getenv(str);
	if (!to_return)
	{
		to_return = search_in_env(str, my_env, exit_code);
		allocated = 1;
	}
	if (*exit_code == ERR_FATAL)
		return (errors_siv(str, allocated, to_return), NULL);
	if (to_return && to_return[0] != '\0')
	{
		result = ft_strdup(to_return);
		if (allocated)
			free(to_return);
		free(str);
		return (result);
	}
	if (allocated)
		free(to_return);
	return (free(str), ft_strdup(""));
}

char	*get_to_expand(char *str, t_istartsub *is, int *exit_code,
				t_env **my_env)
{
	int			i;
	int			j;
	t_istartsub	tmp;
	int			start;
	char		*to_return;

	tmp = *is;
	i = (tmp.i);
	start = (tmp.start);
	j = ++i;
	if (str[j] && str[j] == '?')
		i = j + 1;
	else
	{
		while (expand_need_to_in(str, i))
			i++;
	}
	to_return = ft_substr(str, j, i - j);
	if (!to_return)
		return (*exit_code = ERR_FATAL, NULL);
	start = i;
	to_return = expand_ch(to_return, my_env, exit_code);
	if (*exit_code == ERR_FATAL)
		return (NULL);
	return (tmp.i = i, tmp.start = start, *is = tmp, to_return);
}

char	*expand_segtrot(char *str, t_env **my_env, int *exit_code)
{
	t_istartsub	is;
	char		*expand;
	char		*to_return;

	to_return = init_expand_segtrot(&is);
	if (!to_return)
		return (*exit_code = ERR_FATAL, NULL);
	while (str[is.i])
	{
		while (str[is.i] && (str[is.i] != '$' || (str[is.i] == '$'
					&& str[is.i + 1] && str[is.i + 1] == '$')))
			is.i++;
		to_return = expand_segtrot_gtr(is, str, to_return);
		if (str[is.i] == '$')
		{
			expand = get_to_expand(str, &is, exit_code, my_env);
			if (expand)
			{
				to_return = expand_join_ab(to_return, expand);
				if (!to_return)
					return (*exit_code = ERR_FATAL, NULL);
			}
		}
	}
	return (to_return);
}

t_token	*expand_tokens(t_token	*token, t_env **my_env, int *exit_code)
{
	char		*expanded;
	t_segment	*segtrot;

	if (token->type != WORD)
		return (token);
	segtrot = token->segment;
	while (segtrot)
	{
		if (segtrot->quote_type != S_QUOTED)
		{
			expanded = expand_segtrot(segtrot->value, my_env, exit_code);
			free(segtrot->value);
			segtrot->value = expanded;
		}
		segtrot = segtrot->next;
	}
	return (token);
}
