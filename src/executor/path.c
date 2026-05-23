/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:36:59 by admin             #+#    #+#             */
/*   Updated: 2026/05/23 07:20:02 by admin            ###   ########.fr       */
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
	char	*find_and_check_path(char *cmd, char **path_tab, int *exit_code)
#else
	static char	*find_and_check_path(char *cmd, char **path_tab, int *exit_code)
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
		return (/*err->err = ERR_MALLOC*/ NULL);
	while (path_tab[i])
	{
		path = ft_strjoin(path_tab[i], new_cmd);
		if (!path)
			return (free(new_cmd), /*err->err = ERR_MALLOC,*/ NULL);
		if (!access(path, F_OK | X_OK))
			break ;
		free(path);
		path = NULL;
		i++;
	}
	free(new_cmd);
	return (path);
}

void	print_error(char *cmd, char *file, int *exit_code)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (*exit_code == ERR_CMD)
		ft_putstr_fd("Command not found\n", 2);
	else if (*exit_code == ERR_CMD_FILE)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (*exit_code == ERR_PERMISSION)
		ft_putstr_fd("Permission denied\n", 2);
}

char	*path_orchestrator(char *cmd, t_env **my_env, int *exit_code)
{
	char	*path;
	char	**path_tab;

	path = NULL;
	path_tab = NULL;
	if (!cmd || !my_env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK))
		{
			*exit_code = ERR_CMD_FILE;
			print_error(cmd, NULL, exit_code);
			return (NULL);	
		}
		if (access(cmd, X_OK))
		{
			*exit_code = ERR_PERMISSION;
			print_error(cmd, NULL, exit_code);
			return (NULL);	
		}
		path = ft_strdup(cmd);
		if (!path)
			return (*exit_code = ERR_FATAL, NULL);
	}
	else
	{
		path_tab = extract_paths(cmd, my_env, exit_code);
		path = find_and_check_path(cmd, path_tab, exit_code);
		if (path_tab)
			free_tab(path_tab);
		if (!path && !*exit_code)
		{
			*exit_code = ERR_CMD;
			print_error(cmd, NULL, exit_code);
		}
	}
	return (path);
}
