/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:06:42 by admin             #+#    #+#             */
/*   Updated: 2026/05/23 04:47:41 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_value(char *cmd, t_env *row, int *exit_code)
{
	char	*delimiter;

	delimiter = ft_strchr(cmd, '=');
	if (delimiter)
	{
		if (row->value)
			free(row->value);
		row->value = ft_strdup(delimiter + 1);
		if (!row->value)
			*exit_code = ERR_FATAL;
		row->set_flag = 1;
	}
}

void	append_key(char *cmd, t_env *row, int *exit_code)
{
	int		size;
	char	*delimiter;

	delimiter = ft_strchr(cmd, '=');
	if (!delimiter)
		size = ft_strlen(cmd);
	else
		size = delimiter - cmd;
	row->key = ft_substr(cmd, 0, size);
	if (!row->key)
		*exit_code = ERR_FATAL;
	row->export_flag = 1;
}

static t_env	**resize_my_env(t_env **my_env, int *exit_code, int size)
{
	int		i;
	t_env	**new_env;

	i = 0;
	new_env = ft_calloc(size + 2, sizeof(t_env *));
	if (!new_env)
	{
		*exit_code = ERR_FATAL;
		return (NULL);
	}
	new_env[size] = ft_calloc(1, sizeof(t_env));
	if (!new_env[size])
	{
		*exit_code = ERR_FATAL;
		free(new_env);
		return (NULL);
	}
	while (i < size)
	{
		new_env[i] = my_env[i];
		i++;
	}
	free(my_env);
	return (new_env);
}

t_env	**create_new_row(char *cmd, t_env **my_env, int *exit_code)
{
	int		size;
	t_env	**new_env;

	size = 0;
	while (my_env[size])
		size++;
	new_env = resize_my_env(my_env, exit_code, size);
	if (*exit_code)
		return (NULL);
	append_key(cmd, new_env[size], exit_code);
	append_value(cmd, new_env[size], exit_code);
	return (new_env);
}
