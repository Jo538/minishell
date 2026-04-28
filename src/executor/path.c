/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:36:59 by admin             #+#    #+#             */
/*   Updated: 2026/04/28 20:01:22 by admin            ###   ########.fr       */
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

static int	check_absolute_or_relative_path(char *str)
{
	if (!ft_strchr(str, '/'))
		return (LITERAL);
	return (PATH);
}

#ifdef TESTING
	char	**extract_paths(char **env, t_error *err)
#else
	static char	**extract_paths(char **env, t_error *err)
#endif
{
	int		i;
	int		len;
	char	*path_var;
	char	**path_tab;

	i = 0;
	len = 0;
	path_var = NULL;
	path_tab = NULL;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			len = ft_strlen(env[i]) - 5;
			path_var = ft_substr(env[i], 5, len);
			if (!path_var)
				return (*err = ERR_MALLOC, NULL);
			break ;
		}
		i++;
	}
	path_tab = ft_split(path_var, ':');
	if (!path_tab)
		*err = ERR_MALLOC;
	free(path_var);
	return (path_tab);
}

#ifdef TESTING
	char	*find_and_check_path(char *cmd, char **path_tab, t_error *err)
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
		return (*err = ERR_MALLOC, NULL);
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i], new_cmd);
		if (!path)
		{
			free(new_cmd);
			*err = ERR_MALLOC;
			return (NULL);
		}
		if (!access(path, F_OK | X_OK))
			break ;
		free(path);
		path = NULL;
		i++;
	}
	free(new_cmd);
	return (path);
}

char	*path_orchestrator(char *cmd, char **env, t_error *err)
{
	char	*path;
	char	**path_tab;

	path = NULL;
	path_tab = NULL;
	if (!cmd || !env)
		return (NULL);
	if (check_absolute_or_relative_path(cmd) == PATH)
	{
		path = ft_strdup(cmd);
		if (!path)
			return (*err = ERR_MALLOC, NULL);
		if (access(path, F_OK | X_OK))
		{
			*err = errno;
			free(path);
			path = NULL;	
		}
	}
	else
	{
		path_tab = extract_paths(env, err);
		path = find_and_check_path(cmd, path_tab, err);
		if (!path)
			*err = 127;
	}
	if (path_tab)
		free_tab(path_tab);
	return (path);
}
