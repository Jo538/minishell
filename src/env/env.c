/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 20:26:36 by admin             #+#    #+#             */
/*   Updated: 2026/05/19 17:51:51 by admin            ###   ########.fr       */
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

static void	join_segments(t_env *my_env, char **new_env, int index, t_error *err)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(my_env->key, "=");
	if (!tmp)
	{
		*err = ERR_MALLOC;
		return ;		
	}
	new_env[index] = ft_strjoin(tmp, my_env->value);
	free(tmp);
	if (!new_env)
		*err = ERR_MALLOC;
}

char	**consolidate_my_env(t_env **my_env, t_error *err)
{
	int		i;
	int		j;
	int		size;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = NULL;
	size = find_size(my_env);
	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (*err = ERR_MALLOC, NULL);
	while (my_env[j])
	{		
		if (my_env[j]->export_flag && my_env[j]->set_flag)
		{
			join_segments(my_env[j], new_env, i, err);
			if (*err)
				return (free_tab(new_env), NULL);
			i++;		
		}
		j++;
	}
	return (new_env);
}

void	free_my_env(t_env **my_env)
{
	int	i;

	i = 0;
	while (my_env[i])
	{
		if (my_env[i]->key)
			free(my_env[i]->key);
		if (my_env[i]->value)
			free(my_env[i]->value);
		free(my_env[i]);
		i++;
	}
	free(my_env);
}

static void	fill_table(char **envp, t_env **my_env, int count_var, t_error *err)
{
	int		i;
	int		key_size;
	int		value_size;
	char	*delimiter;

	i = 0;
	key_size = 0;
	value_size = 0;
	delimiter = NULL;
	while (i < count_var)
	{
		my_env[i] = ft_calloc(1, sizeof(t_env));
		if (!my_env[i])
			return(free_my_env(my_env));
		delimiter = ft_strchr(envp[i], '=');
		key_size = delimiter - envp[i];
		my_env[i]->key = ft_substr(envp[i], 0, key_size);
		my_env[i]->value = ft_strdup(delimiter + 1);
		if (!my_env[i]->key || !my_env[i]->value)
			return(free_my_env(my_env));
		my_env[i]->export_flag = 1;
		my_env[i]->set_flag = 1;
		i++;
	}
	my_env[count_var] = NULL;
}

t_env	**env_orchestrator(char **envp, t_error *err)
{
	int		i;
	int		count_var;
	t_env	**my_env;
	char	*delimiter;

	i = 0;
	count_var = 0;
	my_env = NULL;
	delimiter = NULL;
	while (envp[count_var])
		count_var++;
	my_env = ft_calloc(count_var + 1, sizeof(t_env *));
	if (!my_env)
		*err = ERR_MALLOC;
	fill_table(envp, my_env, count_var, err);
	return (my_env);
}
