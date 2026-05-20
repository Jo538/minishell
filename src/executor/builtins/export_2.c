/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:06:42 by admin             #+#    #+#             */
/*   Updated: 2026/05/20 01:12:27 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env **resize_my_env(t_env **my_env, t_error *err, int size)
{
	int		i;
	t_env	**new_env;

	i = 0;
	new_env = NULL;
	new_env = ft_calloc(size, sizeof(t_env *));
	if (!new_env)
	{
		*err = ERR_MALLOC;
		return (NULL);		
	}
	new_env[size] = ft_calloc(1, sizeof(t_env));
	if (!new_env[size])
	{
		*err = ERR_MALLOC;
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

t_env	**create_new_row(char *cmd, t_env **my_env, t_error *err)
{
	int		i;
	int		size;
	t_env	**new_env;

	i = 0;
	size = 0;
	new_env = NULL;
	while (my_env[size])
		size++;
	new_env = resize_my_env(my_env, err, size + 2);
	if (*err)
		return (NULL);
	append_key(cmd, new_env[size], err);
	append_value(cmd, new_env[size], err);
	return (new_env);
}
