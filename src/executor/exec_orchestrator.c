/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_orchestrator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:23:28 by admin             #+#    #+#             */
/*   Updated: 2026/05/26 23:34:59 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	**apply_redirs_and_run_builtin(t_tree *node, t_env **my_env,
	int *exit_code)
{
	char	*cmd;
	int		prev_code;

	cmd = node->argv[0];
	prev_code = *exit_code;
	*exit_code = 0;
	files_redirections_orchestrator(cmd, NULL, node->redirections, exit_code);
	if (*exit_code)
		return (my_env);
	if (!ft_strncmp(cmd, "cd", max(cmd, "cd")))
		run_cd(node->argv, my_env, exit_code);
	else if (!ft_strncmp(cmd, "export", max(cmd, "export")))
		my_env = run_export(node->argv, my_env, exit_code);
	else if (!ft_strncmp(cmd, "unset", max(cmd, "unset")))
		my_env = run_unset(node->argv, my_env, exit_code);
	else if (!ft_strncmp(cmd, "exit", max(cmd, "exit")))
	{
		*exit_code = prev_code;
		run_exit(node->argv, exit_code);
	}
	return (my_env);
}

static t_env	**run_mutate_builtin(t_tree *node, t_env **my_env, int *ec)
{
	int	copy_stdin;
	int	copy_stdout;

	copy_stdin = dup(0);
	copy_stdout = dup(1);
	my_env = apply_redirs_and_run_builtin(node, my_env, ec);
	dup2(copy_stdin, 0);
	close(copy_stdin);
	dup2(copy_stdout, 1);
	close(copy_stdout);
	return (my_env);
}

int	is_a_mutable_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", max(cmd, "cd")))
		return (1);
	if (!ft_strncmp(cmd, "export", max(cmd, "export")))
		return (1);
	if (!ft_strncmp(cmd, "unset", max(cmd, "unset")))
		return (1);
	if (!ft_strncmp(cmd, "exit", max(cmd, "exit")))
		return (1);
	return (0);
}

t_env	**executor(t_tree *node, t_env **my_env, int *exit_code)
{
	if (node->type == NODE_CMD && is_a_mutable_builtin(node->argv[0]))
	{
		my_env = run_mutate_builtin(node, my_env, exit_code);
		return (my_env);
	}
	if (node->type == NODE_CMD)
		cmd_orchestrator(node, my_env, exit_code);
	if (node->type == NODE_PIPE)
		pipe_orchestrator(node, node, my_env, exit_code);
	return (my_env);
}
