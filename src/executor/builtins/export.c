/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:06:42 by admin             #+#    #+#             */
/*   Updated: 2026/05/19 19:28:11 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_var(t_env **my_env)
{
	int	i;

	i = 0;
	while(my_env[i])
	{
		if (my_env[i]->export_flag)
			printf("export %s=\"%s\"\n", my_env[i]->key, my_env[i]->value);
		i++;
	}
}

static int extract_index_delimiter(char *cmd)
{
	int		index;
	char	*delimiter;
	char	*new_key;

	index = ft_strlen(cmd);
	new_key = NULL;
	delimiter = ft_strchr(cmd, '=');
	if (!delimiter)
		return (index);
	index = delimiter - cmd;
	return (index);
}

static t_env	*var_exists(char *cmd, t_env **my_env)
{
	int		i;
	int		index_delimiter;
	char	*new_key;

	i = 0;
	new_key = NULL;
	index_delimiter = extract_index_delimiter(cmd);
	while (my_env[i])
	{
		if (!ft_strncmp(cmd, my_env[i]->key, index_delimiter))
			return (my_env[i]);
		i++;
	}
	return (NULL);
}

static t_env	*append_value(char *cmd, t_env *row)
{
	int	delimiter;

	delimiter = extract_index_delimiter(cmd);
	if (delimiter < ft_strlen(cmd))
	{
		if (row->value)
			free(row->value);
		row->value = ft_strdup(cmd + delimiter + 1);
		row->set_flag = 1;
	}
}

static t_env	*append_key(char *cmd, t_env *row)
{
	int	delimiter;

	delimiter = extract_index_delimiter(cmd);
	row->key = ft_substr(cmd, 0, delimiter);
	row->export_flag = 1;
}

static void	create_new_row(char *cmd, t_env **my_env, t_error *err)
{
	int		i;
	int		size;
	t_env	**new_env;

	i = 0;
	size = 0;
	while (my_env[size])
		size++;
	new_env = ft_calloc(size + 2, sizeof(t_env *));
	if (!new_env)
	{
		*err = ERR_MALLOC;
		return ;
	}
	while (i < size)
	{
		new_env[i] = my_env[i];
		i++;
	}
	new_env[size] = ft_calloc(1, sizeof(t_env));
	if (!new_env[size])
	{
		*err = ERR_MALLOC;
		return ;		
	}
	new_env[size]->key = append_key(cmd, new_env[size]);
	new_env[size]->value = append_value(cmd, new_env[size]);
}

void	run_export(char **cmd, t_env **my_env)
{
	int		size;
	t_env	*var;
	t_env	*new_row;

	size = 0;
	new_row = NULL;
	if (!cmd[1])
	{
		print_var(my_env);
		return ;
	}
	var = var_exists(cmd[1], my_env);
	if (var)
	{
		append_value(cmd[1], var);
		return ;		
	}
	create_new_row();
		
}
