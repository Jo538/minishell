/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:36:59 by admin             #+#    #+#             */
/*   Updated: 2026/04/27 22:53:32 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_absolute_or_relative_path(char *str)
{
	if (ft_strchr(str, '/') == NULL)
		return (LITERAL);
	return (PATH);
}

char	**extract_paths(char **env, t_error *err)
{
	int		i;
	int		len;
	char	*path_var;
	char	**path_tab;

	i = 0;
	len = 0;
	path_var = NULL;
	path_tab = NULL;
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

char	*find_and_check_path(char *cmd, char **path_tab, t_error *err)
{
	int		i;
	char	*path;
	char	*new_cmd;
	
	i = 0;
	path = NULL;
	new_cmd = ft_strjoin(cmd, "/");
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
		if (access(path, F_OK | X_OK))
			break ;
		free(path);
		path = NULL;
		i++;
	}
	return (path);
}



