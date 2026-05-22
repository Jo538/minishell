/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:36:59 by admin             #+#    #+#             */
/*   Updated: 2026/05/23 00:20:53 by admin            ###   ########.fr       */
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

#ifdef TESTING
	char	**extract_paths(char *cmd, char **env, t_error_exec *err)
#else
	static char	**extract_paths(char *cmd, t_env **my_env, t_error *err)
#endif
{
	int		i;
	char	*path_value;
	char	**path_tab;

	i = 0;
	path_value = NULL;
	path_tab = NULL;
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
		return (err->err = ENOENT, err->operation = OPEN_CMD, err->cmd = cmd, NULL);
	path_tab = ft_split(path_value, ':');
	if (!path_tab)
		err->err = ERR_MALLOC;
	return (path_tab);
}

#ifdef TESTING
	char	*find_and_check_path(char *cmd, char **path_tab, t_error_exec *err)
#else
	static char	*find_and_check_path(char *cmd, char **path_tab, t_error *err)
#endif
{
	int		i;
	char	*path;
	char	*new_cmd;
	
	i = 0;
	path = NULL;
	if (!cmd || !*cmd || !path_tab)
		return (NULL);
	new_cmd = ft_strjoin("/", cmd);
	if (!new_cmd)
		return (err->err = ERR_MALLOC, NULL);
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i], new_cmd);
		if (!path)
			return (free(new_cmd), err->err = ERR_MALLOC, NULL);
		if (!access(path, F_OK | X_OK))
			break ;
		free(path);
		path = NULL;
		i++;
	}
	free(new_cmd);
	return (path);
}

char	*path_orchestrator(char *cmd, t_env **my_env, t_error *err)
{
	char	*path;
	char	**path_tab;

	path = NULL;
	path_tab = NULL;
	if (!cmd || !my_env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		path = ft_strdup(cmd);
		if (!path)
			return (*err = ERR_FATAL, NULL);
		if (access(path, F_OK | X_OK))
			return (*err = errno, err->operation = OPEN_CMD, err->cmd = cmd, free(path), NULL);	
	}
	else
	{
		path_tab = extract_paths(cmd, my_env, err);
		path = find_and_check_path(cmd, path_tab, err);
	if (path_tab)
		free_tab(path_tab);
		if (!path && !err->err)
			return (err->err = 127, err->cmd = cmd, NULL);
	}
	return (path);
}
