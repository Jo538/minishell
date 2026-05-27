/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:04:28 by admin             #+#    #+#             */
/*   Updated: 2026/05/26 23:39:46 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_in_env(t_env **my_env, char *key)
{
	int	i;
	int	len;

	len = ft_strlen(key);
	i = 0;
	while (my_env[i])
	{
		if ((int)ft_strlen(my_env[i]->key) == len
			&& !ft_strncmp(my_env[i]->key, key, len))
			return (my_env[i]->value);
		i++;
	}
	return (NULL);
}

static void	set_env_value(t_env **my_env, char *key, char *value)
{
	int	i;
	int	len;

	if (!value)
		return ;
	len = ft_strlen(key);
	i = 0;
	while (my_env[i])
	{
		if ((int)ft_strlen(my_env[i]->key) == len
			&& !ft_strncmp(my_env[i]->key, key, len))
		{
			if (my_env[i]->value)
				free(my_env[i]->value);
			my_env[i]->value = ft_strdup(value);
			my_env[i]->set_flag = 1;
			return ;
		}
		i++;
	}
}

static char	*resolve_target(char **cmd, t_env **my_env, int *exit_code)
{
	int		count;
	char	*target;

	count = 0;
	while (cmd[count])
		count++;
	if (count > 2)
	{
		error_orchestrator(exit_code, ERR_TOO_MANY_ARGS, cmd[0], NULL);
		return (NULL);
	}
	if (count == 1)
	{
		target = find_in_env(my_env, "HOME");
		if (!target)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			*exit_code = 1;
		}
		return (target);
	}
	return (cmd[1]);
}

void	run_cd(char **cmd, t_env **my_env, int *exit_code)
{
	char	*target;
	char	old_pwd[4096];
	char	new_pwd[4096];

	target = resolve_target(cmd, my_env, exit_code);
	if (!target)
		return ;
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = 0;
	if (chdir(target) == -1)
	{
		error_orchestrator(exit_code, ERR_FILE, cmd[0], target);
		return ;
	}
	if (getcwd(new_pwd, sizeof(new_pwd)))
	{
		set_env_value(my_env, "OLDPWD", old_pwd);
		set_env_value(my_env, "PWD", new_pwd);
	}
}
