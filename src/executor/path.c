/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:36:59 by admin             #+#    #+#             */
/*   Updated: 2026/06/04 19:08:13 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**extract_paths(t_env **my_env)
{
	int		i;
	char	*path_value;

	i = 0;
	path_value = NULL;
	if (!my_env)
		return (NULL);
	while (my_env[i])
	{
		if (!ft_strncmp(my_env[i]->key, "PATH", 4))
		{
			path_value = my_env[i]->value;
			break ;
		}
		i++;
	}
	if (!path_value)
		return (NULL);
	return (ft_split(path_value, ':'));
}

static char	*find_and_check_path(char *cmd, char **path_tab, int *error)
{
	int		i;
	char	*path;
	char	*new_cmd;

	i = 0;
	if (!cmd || !*cmd || !path_tab)
		return (NULL);
	new_cmd = ft_strjoin("/", cmd);
	if (!new_cmd)
		return (NULL);
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i], new_cmd);
		if (!path)
			return (free(new_cmd), NULL);
		if (!access(path, X_OK))
			return (free(new_cmd), path);
		if (!access(path, F_OK))
			return (free(path), free(new_cmd), *error = ERR_CMD_PERMISSION, NULL);
		free(path);
		i++;
	}
	free(new_cmd);
	*error = ERR_CMD;
	return (NULL);
}

static char	*resolve_absolute_path(char *cmd, int *exit_code)
{
	struct stat	st;
	char		*path;

	stat(cmd, &st);
	if (S_ISDIR(st.st_mode))
	{
		error_orchestrator(exit_code, ERR_IS_DIRECTORY, cmd, NULL);
		return (NULL);
	}
	if (access(cmd, F_OK | X_OK))
	{
		error_with_errno(exit_code, OPEN_CMD, cmd, NULL);
		return (NULL);
	}
	path = ft_strdup(cmd);
	if (!path)
		*exit_code = ERR_FATAL;
	return (path);
}

char	*path_orchestrator(char *cmd, t_env **my_env, int *exit_code)
{
	int		error;
	char	*path;
	char	**path_tab;

	error = 0;
	if (!cmd || !my_env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (resolve_absolute_path(cmd, exit_code));
	path_tab = extract_paths(my_env);
	path = find_and_check_path(cmd, path_tab, &error);
	if (path_tab)
		free_tab(path_tab);
	if (error)
		error_orchestrator(exit_code, error, cmd, NULL);
	return (path);
}
