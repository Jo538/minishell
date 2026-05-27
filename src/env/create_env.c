/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 20:26:36 by admin             #+#    #+#             */
/*   Updated: 2026/05/27 12:00:00 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	fill_env_row(t_env *row, char *src)
{
	char	*delimiter;
	int		key_size;

	delimiter = ft_strchr(src, '=');
	key_size = delimiter - src;
	row->key = ft_substr(src, 0, key_size);
	row->value = ft_strdup(delimiter + 1);
	if (!row->key || !row->value)
		return (0);
	row->export_flag = 1;
	row->set_flag = 1;
	return (1);
}

static void	fill_table(char **envp, t_env **my_env, int count_var,
	int *exit_code)
{
	int	i;

	i = 0;
	while (i < count_var)
	{
		my_env[i] = ft_calloc(1, sizeof(t_env));
		if (!my_env[i] || !fill_env_row(my_env[i], envp[i]))
		{
			*exit_code = ERR_FATAL;
			free_my_env(my_env);
			return ;
		}
		i++;
	}
	my_env[count_var] = NULL;
}

t_env	**create_env(char **envp, int *exit_code)
{
	int		count_var;
	t_env	**my_env;

	count_var = 0;
	while (envp[count_var])
		count_var++;
	my_env = ft_calloc(count_var + 1, sizeof(t_env *));
	if (!my_env)
		return (*exit_code = ERR_FATAL, NULL);
	fill_table(envp, my_env, count_var, exit_code);
	return (my_env);
}
