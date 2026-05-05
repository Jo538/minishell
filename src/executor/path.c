/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:36:59 by admin             #+#    #+#             */
/*   Updated: 2026/05/05 23:21:37 by admin            ###   ########.fr       */
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

static char *malloc_path_var_when_found(char *var, t_error_exec *err)
{
	int		len;
	int		i;
	char	*path_var;
	
	path_var = NULL;
	i = 0;
	len = ft_strlen(var) - 5;
	path_var = ft_substr(var, 5, len);
	if (!path_var)
		err->err = ERR_MALLOC;
	return (path_var);
}
#ifdef TESTING
	char	**extract_paths(char *cmd, char **env, t_error_exec *err)
#else
	static char	**extract_paths(char *cmd, char **env, t_error_exec *err)
#endif
{
	int		i;
	char	*path_var;
	char	**path_tab;

	i = 0;
	path_var = NULL;
	path_tab = NULL;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path_var = malloc_path_var_when_found(env[i], err);
			break ;
		}
		i++;
	}
	if (!path_var)
		return (err->err = ENOENT, err->operation = CMD_OPE, err->cmd = cmd, NULL);
	path_tab = ft_split(path_var, ':');
	if (!path_tab)
		err->err = ERR_MALLOC;
	return (free(path_var), path_tab);
}

#ifdef TESTING
	char	*find_and_check_path(char *cmd, char **path_tab, t_error_exec *err)
#else
	static char	*find_and_check_path(char *cmd, char **path_tab, t_error_exec *err)
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

char	*path_orchestrator(char *cmd, char **env, t_error_exec *err)
{
	char	*path;
	char	**path_tab;

	path = NULL;
	path_tab = NULL;
	if (!cmd || !env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		path = ft_strdup(cmd);
		if (!path)
			return (err->err = ERR_MALLOC, NULL);
		if (access(path, F_OK | X_OK))
			return (err->err = errno, err->operation = CMD_OPE, err->cmd = cmd, free(path), NULL);	
	}
	else
	{
		path_tab = extract_paths(cmd, env, err);
		path = find_and_check_path(cmd, path_tab, err);
	if (path_tab)
		free_tab(path_tab);
		if (!path && !err->err)
			return (err->err = 127, err->cmd = cmd, NULL);
	}
	return (path);
}
