/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_orchestrator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:27:25 by admin             #+#    #+#             */
/*   Updated: 2026/05/21 22:27:37 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_tree *node)
{
	if (!ft_strncmp("cd", node->argv[0], 2))
		return (1);
	if (!ft_strncmp("echo", node->argv[0], 4))
		return (1);
	if (!ft_strncmp("env", node->argv[0], 3))
		return (1);
	if (!ft_strncmp("exit", node->argv[0], 4))
		return (1);
	if (!ft_strncmp("export", node->argv[0], 6))
		return (1);
	if (!ft_strncmp("pwd", node->argv[0], 3))
		return (1);
	if (!ft_strncmp("unset", node->argv[0], 5))
		return (1);
	return (0);
}

void	builtin_orchestrator(t_tree *node, t_env **my_env, t_error_exec *err)
{
	if (!ft_strncmp("cd", node->argv[0], 2))
		run_cd(node->argv, err);
	if (!ft_strncmp("echo", node->argv[0], 4))
		run_echo(node->argv);
	if (!ft_strncmp("env", node->argv[0], 3))
		run_env(my_env);
	if (!ft_strncmp("exit", node->argv[0], 4))
		run_exit(node->argv, err);
	if (!ft_strncmp("export", node->argv[0], 6))
		run_export(node->argv, my_env, err);
	if (!ft_strncmp("pwd", node->argv[0], 3))
		run_pwd();
	if (!ft_strncmp("unset", node->argv[0], 5))
		run_unset(node->argv, my_env, err);
}
