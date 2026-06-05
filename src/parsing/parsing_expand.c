/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:18:40 by benji             #+#    #+#             */
/*   Updated: 2026/06/05 14:00:49 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_in_env(char *str, t_env **my_env, int *exit)
{
	int	i;
	char	*tmp;
	i = 0;
	if (str[0] == '?')
	{
		tmp = ft_itoa(*exit);
		if (!tmp)
			return (*exit = ERR_FATAL, NULL);
		return (tmp);
	}
	if (str[0] == ' ' || str[0] == '\0')
	{
		tmp = ft_strdup("$");
		if (!tmp)
			return (*exit = ERR_FATAL, NULL);
		return (tmp);
	}
	while (my_env[i])
	{
		if (ft_strlen(my_env[i]->key) == ft_strlen(str) &&
			!(ft_strncmp(my_env[i]->key, str, ft_strlen(str))))
		{
			return (my_env[i]->value);
		}
		i++;
	}
	return (NULL);
}

char	*expand_ch(char *str, t_env **my_env, int *exit_code)
{
	char	*to_return;

	to_return = getenv(str);//ICI PENSER A AJOUTER LE CAS DE $?
	if (!to_return)
		to_return = search_in_env(str ,my_env, exit_code);
	free(str);
	if (*exit_code == ERR_FATAL)
		return (NULL);
	return (to_return);
}

char	*get_to_expand(char *str, int *to_i, int *to_start, int *exit_code, t_env **my_env)
{
	int		i;
	int		j;
	int		start;

	char	*to_return;
	i = *(to_i);
	start = *(to_start);
	i++;
	j = i;
	if (str[j] && str[j] == '?')
		i = j + 1;
	else
	{
		while (str[i] && str[i] != '$' && str[i] != ' ')
			i++;
	}
	to_return = ft_substr(str, j, i - j);
	if (!to_return)
		return (*exit_code = ERR_FATAL, NULL);
	start = i;
	to_return = expand_ch(to_return, my_env, exit_code);
	if (*exit_code == ERR_FATAL)
		return (NULL);
	(*to_i) = i;
	(*to_start) = start;
	return (to_return);
}

char	*expand_segtrot(char *str, t_env **my_env, int *exit_code)
{
	int		i;
	int		start;
	char	*sub;
	char	*expand;
	char	*to_return;
	char	*tmp;

	i = 0;
	start = 0;
	to_return = malloc(1);
	if (!to_return)
		return (NULL);
	to_return[0] = 0;
	while (str[i])
	{
		while (str[i] && (str[i] != '$' || (str[i] == '$' && str[i + 1] && str[i + 1] == '$')))
			i++;
		sub = ft_substr(str, start, i - start);
		if (!sub)
			return (free(to_return), *exit_code = ERR_FATAL, NULL);
		tmp = to_return;
		to_return = ft_strjoin(to_return, sub);
		free(tmp);
		free(sub);
		if (!to_return)
			return (*exit_code = ERR_FATAL, NULL);
		if (str[i] == '$')
		{
			expand = get_to_expand(str, &i, &start, exit_code, my_env);
			if (expand)
			{
				tmp = to_return;
				to_return = ft_strjoin(to_return, expand);
				if (!to_return)
				{
					free(tmp);
					free(expand);
					return (*exit_code = ERR_FATAL, NULL);
				}
				free(tmp);
				free(expand);
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
			expanded = expand_segtrot(segtrot->value, my_env, exit_code); //il y a encore le cas de $$ a gerer et d autres scases type $? (la ca ne gere que les cas ultras classiques)
			free(segtrot->value);
			segtrot->value = expanded;
		}
		segtrot = segtrot->next;
	}
	return (token); //necessite a faire
}
