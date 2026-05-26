/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:06:42 by admin             #+#    #+#             */
/*   Updated: 2026/05/23 04:47:41 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env **resize_my_env(t_env **my_env, int *exit_code, int size)
{
	int		i;
	t_env	**new_env;

	i = 0;
	new_env = NULL;
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
	int		i;
	int		size;
	t_env	**new_env;

	i = 0;
	size = 0;
	new_env = NULL;
	while (my_env[size])
		size++;
	new_env = resize_my_env(my_env, exit_code, size);
	if (*exit_code)
		return (NULL);
	append_key(cmd, new_env[size], exit_code);
	append_value(cmd, new_env[size], exit_code);
	return (new_env);
}
