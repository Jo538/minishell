/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:42:39 by admin             #+#    #+#             */
/*   Updated: 2026/05/26 02:33:21 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(int *pipefd, t_tree *node, t_env **my_env, int *exit_code)
{
	char **	env;
	char	*path;
	
	path = NULL;
	files_redirections_orchestrator(node->argv[0], pipefd, node->redirections, exit_code);
	if (*exit_code)
		free_and_exit(node, my_env, exit_code);
	if (is_builtin(node))
		builtin_orchestrator(node, node, my_env, exit_code);
	path = path_orchestrator(node->argv[0], my_env, exit_code);
	if (!path)
		free_and_exit(node, my_env, exit_code);
	env = consolidate_my_env(my_env, exit_code);
	execve(path, node->argv, env);
}

int	inspect_child_status(pid_t child, int status)
{
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);	
}

void	cmd_orchestrator(t_tree *node, t_env **my_env, int *exit_code)
{
	int		status;
	pid_t	child;
	
	child = -1;
	status = -1;
	child = fork();
	if (child == -1)
	{
		*exit_code = ERR_FATAL;
		return ;		
	}
	if (child == 0)
		child_process(NULL, node, my_env, exit_code);
	*exit_code = inspect_child_status(child, status);
}
