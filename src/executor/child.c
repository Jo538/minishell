/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:42:39 by admin             #+#    #+#             */
/*   Updated: 2026/06/09 23:38:01 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(int *pipefd, t_tree *node, t_env **my_env, int *exit_code)
{
	char	**env;
	char	*path;

	path = NULL;
	*exit_code = 0;
	files_redirections_orchestrator(node->argv[0], pipefd,
		node->redirections, exit_code);
	if (*exit_code)
		free_and_exit(node, my_env, exit_code);
	if (is_builtin(node))
		builtin_orchestrator(node, node, my_env, exit_code);
	path = path_orchestrator(node->argv[0], my_env, exit_code);
	if (!path)
		free_and_exit(node, my_env, exit_code);
	env = consolidate_my_env(my_env, exit_code);
	execve(path, node->argv, env);
	*exit_code = EISDIR;
	printf("macro: %d\n", *exit_code);
	error_with_errno(exit_code, -1, node->argv[0], NULL);
	free(path);
	if (env)
		free_tab(env);
	free_and_exit(node, my_env, exit_code);
}

int	inspect_child_status(pid_t child, int *pipefd, pid_t other)
{
	int	status;
	int	sig;

	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (other > 0)
		waitpid(other, NULL, 0);
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit: 3\n", 8);
		return (128 + sig);
	}
	return (0);
}

void	cmd_orchestrator(t_tree *node, t_env **my_env, int *exit_code)
{
	pid_t	child;

	child = -1;
	sig_executing();
	child = fork();
	if (child == -1)
	{
		*exit_code = ERR_FATAL;
		return ;
	}
	if (child == 0)
	{
		sig_child();
		child_process(NULL, node, my_env, exit_code);
	}
	*exit_code = inspect_child_status(child, NULL, -1);
}
