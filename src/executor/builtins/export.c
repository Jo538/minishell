/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:06:42 by admin             #+#    #+#             */
/*   Updated: 2026/06/04 19:36:56 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(char *cmd)
{
	int		i;
	int		size;
	char	*delimiter;

	delimiter = ft_strchr(cmd, '=');
	if (delimiter)
		size = delimiter - cmd;
	else
		size = ft_strlen(cmd);
	if (size == 0)
		return (0);
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
		return (0);
	i = 1;
	while (i < size)
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static t_env	*search_key(char *cmd, t_env **my_env)
{
	int		i;
	int		size;
	char	*delimiter;

	i = 0;
	delimiter = ft_strchr(cmd, '=');
	if (!delimiter)
		size = ft_strlen(cmd);
	else
		size = delimiter - cmd;
	while (my_env[i])
	{
		if ((int)ft_strlen(my_env[i]->key) == size
			&& !ft_strncmp(cmd, my_env[i]->key, size))
			return (my_env[i]);
		i++;
	}
	return (NULL);
}

static t_env	**add_or_update(char *cmd, t_env **my_env, int *exit_code)
{
	t_env	*key;

	key = search_key(cmd, my_env);
	if (key)
		append_value(cmd, key, exit_code);
	else
		my_env = create_new_row(cmd, my_env, exit_code);
	return (my_env);
}

t_env	**run_export(char **cmd, t_env **my_env, int *exit_code)
{
	int	i;

	i = 1;
	if (!cmd[1])
		return (print_var(my_env), my_env);
	while (cmd[i])
	{
		if (!is_valid_key(cmd[i]))
		{
			error_orchestrator(exit_code, ERR_INVALID_IDENTIFIER,
				cmd[0], cmd[i]);
			break ;
		}
		my_env = add_or_update(cmd[i], my_env, exit_code);
		if (*exit_code)
			break ;
		i++;
	}
	return (my_env);
}
