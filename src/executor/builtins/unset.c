/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 21:13:51 by admin             #+#    #+#             */
/*   Updated: 2026/05/20 23:19:58 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_key(char *cmd, t_env **my_env)
{
	int		i;
	int		size;
	char	*new_key;
	char	*delimiter;

	i = 0;
	new_key = NULL;
	delimiter = ft_strchr(cmd, '=');
	if (!delimiter)
		size = ft_strlen(cmd);
	else
		size = delimiter - cmd;
	while (my_env[i])
	{
		if (!ft_strncmp(cmd, my_env[i]->key, size))
			return (i);
		i++;
	}
	return (-1);
}

static t_env **resize_my_env(t_env **my_env, int size, int index, t_error *err)
{
	t_env	**new_env;

	new_env = ft_calloc(size, sizeof(t_env *));
	if (!new_env)
	{
		*err = ERR_MALLOC;
		return (NULL);		
	}
	free(my_env[index]->key);
	if (my_env[index]->value)
		free(my_env[index]->value);
	free(my_env[index]);
	return (new_env);
}

int	find_size_array(t_env **my_env)
{
	int	i;
	
	i = 0;
	while (my_env[i])
		i++;
	return (i);
}

static void	fill_new_env(t_env **new_env, t_env **my_env, int index, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (i == index)
		{
			i++;
			continue ;			
		}
		new_env[j] = my_env[i];
		i++;
		j++;
	}
	free(my_env);
}

t_env	**run_unset(char **cmd, t_env ** my_env, t_error *err)
{
	int	i;
	int	size;
	int	key_index;
	t_env	**new_env;

	if (!cmd[1])
		return (my_env);
	i = 1;
	while (cmd[i])
	{
		size = find_size_array(my_env);
		key_index = search_key(cmd[i], my_env);
		if (key_index != -1)
		{
			new_env = resize_my_env(my_env, size, key_index, err);
			fill_new_env(new_env, my_env, key_index, size);
			my_env = new_env;
		}
		i++;	
	}
	return (my_env);
}
