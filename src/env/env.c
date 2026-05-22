/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 20:26:36 by admin             #+#    #+#             */
/*   Updated: 2026/05/23 00:50:46 by admin            ###   ########.fr       */
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

static void	fill_table(char **envp, t_env **my_env, int count_var, int *exit_code)
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
		{
			*exit_code = ERR_FATAL;
			free_my_env(my_env);
			my_env = NULL;
			return ;
		}
		delimiter = ft_strchr(envp[i], '=');
		key_size = delimiter - envp[i];
		my_env[i]->key = ft_substr(envp[i], 0, key_size);
		my_env[i]->value = ft_strdup(delimiter + 1);
		if (!my_env[i]->key || !my_env[i]->value)
		{
			*exit_code = ERR_FATAL;
			free_my_env(my_env);
			my_env = NULL;
			return ;
		}
		my_env[i]->export_flag = 1;
		my_env[i]->set_flag = 1;
		i++;
	}
	my_env[count_var] = NULL;
}

t_env	**create_env(char **envp, int *exit_code)
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
		return (*exit_code = ERR_FATAL, NULL);		
	fill_table(envp, my_env, count_var, exit_code);
	return (my_env);
}
