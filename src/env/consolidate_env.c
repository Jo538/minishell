/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consolidate_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:00:00 by admin             #+#    #+#             */
/*   Updated: 2026/05/27 12:00:00 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_size(t_env **my_env)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (my_env[i])
	{
		if (my_env[i]->export_flag && my_env[i]->set_flag)
			size++;
		i++;
	}
	return (size);
}

static void	join_segments(t_env *my_env, char **new_env, int index,
	int *exit_code)
{
	char	*tmp;

	tmp = ft_strjoin(my_env->key, "=");
	if (!tmp)
	{
		*exit_code = ERR_FATAL;
		return ;
	}
	new_env[index] = ft_strjoin(tmp, my_env->value);
	free(tmp);
	if (!new_env[index])
		*exit_code = ERR_FATAL;
}

char	**consolidate_my_env(t_env **my_env, int *exit_code)
{
	int		i;
	int		j;
	int		size;
	char	**new_env;

	i = 0;
	j = 0;
	size = find_size(my_env);
	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (*exit_code = ERR_FATAL, NULL);
	while (my_env[j])
	{
		if (my_env[j]->export_flag && my_env[j]->set_flag)
		{
			join_segments(my_env[j], new_env, i, exit_code);
			if (*exit_code)
				return (free_tab(new_env), NULL);
			i++;
		}
		j++;
	}
	return (new_env);
}
