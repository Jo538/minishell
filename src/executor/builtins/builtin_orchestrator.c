/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_orchestrator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 22:27:25 by admin             #+#    #+#             */
/*   Updated: 2026/05/24 01:52:00 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirections(t_tree *node)
{
	t_redir	*tmp;

	tmp = node->redirections;
	while (node->redirections)
	{
		free(node->redirections->file);
		tmp = node->redirections->next;
		free(node->redirections);	
		node->redirections = tmp;	
	}
}

void	free_node(t_tree *node)
{
	int i = 0;
	while (node->argv[i])
	{
		free(node->argv[i]);
		i++;
	}
	free(node->argv);
	if (node->redirections)
		free_redirections(node);
	free(node);
}

static int	max(char *str1, char *str2)
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

void	builtin_orchestrator(t_tree *node, t_env **my_env, int *exit_code)
{
	if (!ft_strncmp("cd", node->argv[0], 2))
		run_cd(node->argv, exit_code);
	if (!ft_strncmp("echo", node->argv[0], 4))
		run_echo(node->argv);
	if (!ft_strncmp("env", node->argv[0], 3))
		run_env(my_env);
	if (!ft_strncmp("exit", node->argv[0], 4))
		run_exit(node->argv, exit_code);
	if (!ft_strncmp("export", node->argv[0], 6))
		run_export(node->argv, my_env, exit_code);
	if (!ft_strncmp("pwd", node->argv[0], 3))
		run_pwd();
	if (!ft_strncmp("unset", node->argv[0], 5))
		run_unset(node->argv, my_env, exit_code);
	free_node(node);
	free_my_env(my_env);
	exit(*exit_code);
}
