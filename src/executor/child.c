/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:42:39 by admin             #+#    #+#             */
/*   Updated: 2026/05/23 07:05:00 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors(int *exit_code)
{
	// ft_putstr_fd(err->cmd, 2);
	// if (err->err == 127)
	// 	ft_putendl_fd(": Command not found", 2);
	// if (err->err == ENOENT)
	// {
	// 	ft_putendl_fd(": No such file or directory", 2);
	// 	if (err->operation == OPEN_CMD)
	// 		exit(127);	
	// 	if (err->operation == OPEN_FILE)
	// 		exit(1);		
	// }
	// if (err->err == EACCES)
	// {
	// 	ft_putendl_fd(": Permission denied", 2);
	// 	if (err->operation == OPEN_CMD)
	// 		exit(126);	
	// 	if (err->operation == OPEN_FILE)
	// 		exit(1);	
	// }
	// exit(err->err);
}

void	free_and_exit(t_tree *node, t_env **my_env, int *exit_code)
{
	free_node(node);
	free_my_env(my_env);
	exit(*exit_code);
}

void	child_process(int *pipefd, t_tree *node, t_env **my_env, int *exit_code)
{
	char **	env;
	char	*path;
	
	path = NULL;
	files_redirections_orchestrator(pipefd, node->redirections, exit_code);
	if (*exit_code)
		errors(exit_code);
	if (is_builtin(node))
		builtin_orchestrator(node, my_env, exit_code);
	path = path_orchestrator(node->argv[0], my_env, exit_code);
	if (!path)
		free_and_exit(node, my_env, exit_code);
	env = consolidate_my_env(my_env, exit_code);
	execve(path, node->argv, env);
	*exit_code = errno;
	errors(exit_code);	
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
