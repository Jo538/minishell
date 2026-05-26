/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:36:59 by admin             #+#    #+#             */
/*   Updated: 2026/05/25 19:27:32 by admin            ###   ########.fr       */
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
	char	**extract_paths(char *cmd, t_env **my_env, int *exit_code)
#else
	static char	**extract_paths(char *cmd, t_env **my_env, int *exit_code)
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
		return (/*err->err = ENOENT, err->operation = OPEN_CMD, err->cmd = cmd,*/ NULL);
	path_tab = ft_split(path_value, ':');
	/*if (!path_tab)
		err->err = ERR_MALLOC;*/
	return (path_tab);
}

#ifdef TESTING
	char	*find_and_check_path(char *cmd, char **path_tab, int *error)
#else
	static char	*find_and_check_path(char *cmd, char **path_tab, int *error)
#endif
{
	int		i;
	char	*path;
	char	*new_cmd;
	
	i = 0;
	if (!cmd || !*cmd || !path_tab)
		return (NULL);
	new_cmd = ft_strjoin("/", cmd);
	if (!new_cmd)
		return (/*err->err = ERR_MALLOC*/ NULL);
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i], new_cmd);
		if (!path)
			return (free(new_cmd), NULL);
		if (!access(path, F_OK))
		{
			if (!access(path, X_OK))
				return (free(new_cmd), path);
			return (free(path), free(new_cmd), *error = ERR_PERMISSION, NULL);
		}
		free(path);
		i++;
	}
	free(new_cmd);
	*error = ERR_CMD;
	return (NULL);
}

char	*path_orchestrator(char *cmd, t_env **my_env, int *exit_code)
{
	int		error = 0;
	char	*path;
	char	**path_tab;

	path = NULL;
	path_tab = NULL;
	if (!cmd || !my_env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK))
		{
			error_orchestrator(exit_code, 1, errno, OPEN_CMD, cmd, NULL);
			return (NULL);	
		}
		path = ft_strdup(cmd);
		if (!path)
			return (*exit_code = ERR_FATAL, NULL);
	}
	else
	{
		path_tab = extract_paths(cmd, my_env, exit_code);
		path = find_and_check_path(cmd, path_tab, &error);
		if (path_tab)
			free_tab(path_tab);
		if (error)
			error_orchestrator(exit_code, 0, error, OPEN_CMD, cmd, NULL);
	}
	return (path);
}
