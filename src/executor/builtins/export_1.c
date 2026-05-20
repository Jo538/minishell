/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:06:42 by admin             #+#    #+#             */
/*   Updated: 2026/05/20 18:17:37 by admin            ###   ########.fr       */
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
			printf("export %s", my_env[i]->key);
		if (my_env[i]->value)
			printf("=\"%s\"\n", my_env[i]->value);
		else
			printf("%c", '\n');
		i++;
	}
}

static t_env	*search_key(char *cmd, t_env **my_env)
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
			return (my_env[i]);
		i++;
	}
	return (NULL);
}

void	append_value(char *cmd, t_env *row, t_error *err)
{
	int		index;
	char	*delimiter;

	index = 0;
	delimiter = ft_strchr(cmd, '=');
	if (delimiter)
	{
		if (row->value)
			free(row->value);
		row->value = ft_strdup(delimiter + 1);
		if (!row->value)
			*err = ERR_MALLOC;
		row->set_flag = 1;
	}
}

void	append_key(char *cmd, t_env *row, t_error *err)
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
		*err = ERR_MALLOC;
	row->export_flag = 1;
}

t_env	**run_export(char **cmd, t_env **my_env, t_error *err)
{
	int		size;
	t_env	*key;
	t_env	*new_row;

	size = 0;
	new_row = NULL;
	if (!cmd[1])
		print_var(my_env);
	else
	{
		key = search_key(cmd[1], my_env);
		if (key)
		{
			append_value(cmd[1], key, err);
			if (*err)
				return (NULL);			
		}	
		else
			my_env = create_new_row(cmd[1], my_env, err);
	}
	return (my_env);
}
