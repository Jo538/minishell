/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_orchestrator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:27:25 by admin             #+#    #+#             */
/*   Updated: 2026/06/02 14:17:16 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	max(char *str1, char *str2)
{
	int	size1;
	int	size2;

	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	if (size1 < size2)
		return (size2);
	return (size1);
}

int	is_builtin(t_tree *node)
{
	if (!node->argv[0])
		return (0);
	if (!ft_strncmp("cd", node->argv[0], max("cd", node->argv[0])))
		return (1);
	if (!ft_strncmp("echo", node->argv[0], max("echo", node->argv[0])))
		return (1);
	if (!ft_strncmp("env", node->argv[0], max("env", node->argv[0])))
		return (1);
	if (!ft_strncmp("exit", node->argv[0], max("exit", node->argv[0])))
		return (1);
	if (!ft_strncmp("export", node->argv[0], max("export", node->argv[0])))
		return (1);
	if (!ft_strncmp("pwd", node->argv[0], max("pwd", node->argv[0])))
		return (1);
	if (!ft_strncmp("unset", node->argv[0], max("unset", node->argv[0])))
		return (1);
	return (0);
}

void	builtin_orchestrator(t_tree *root, t_tree *node, t_env **my_env,
	int *exit_code)
{
	int	prev_code;

	prev_code = *exit_code;
	*exit_code = 0;
	if (!ft_strncmp("cd", node->argv[0], max("cd", node->argv[0])))
		run_cd(node->argv, my_env, exit_code);
	else if (!ft_strncmp("echo", node->argv[0], max("echo", node->argv[0])))
		run_echo(node->argv);
	else if (!ft_strncmp("env", node->argv[0], max("env", node->argv[0])))
		run_env(node->argv, my_env, exit_code);
	else if (!ft_strncmp("exit", node->argv[0], max("exit", node->argv[0])))
	{
		*exit_code = prev_code;
		run_exit(node->argv, exit_code);
	}
	else if (!ft_strncmp("export", node->argv[0], max("export", node->argv[0])))
		run_export(node->argv, my_env, exit_code);
	else if (!ft_strncmp("pwd", node->argv[0], max("pwd", node->argv[0])))
		run_pwd();
	else if (!ft_strncmp("unset", node->argv[0], max("unset", node->argv[0])))
		run_unset(node->argv, my_env, exit_code);
	free_and_exit(root, my_env, exit_code);
}
