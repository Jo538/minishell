/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 23:54:46 by admin             #+#    #+#             */
/*   Updated: 2026/06/04 11:43:26 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_redirections(char direction, int *pipefd)
{
	if (direction == 'L')
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (direction == 'R')
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

static void	exec_in_pipe(t_tree *root, t_tree *cmd_node, t_env **my_env,
	int *exit_code)
{
	char	**env;
	char	*path;
	int		prev_code;

	prev_code = *exit_code;
	*exit_code = 0;
	files_redirections_orchestrator(cmd_node->argv[0], NULL,
		cmd_node->redirections, exit_code);
	if (*exit_code)
		free_and_exit(root, my_env, exit_code);
	*exit_code = prev_code;
	if (is_builtin(cmd_node))
		builtin_orchestrator(root, cmd_node, my_env, exit_code);
	path = path_orchestrator(cmd_node->argv[0], my_env, exit_code);
	if (*exit_code)
		free_and_exit(root, my_env, exit_code);
	env = consolidate_my_env(my_env, exit_code);
	execve(path, cmd_node->argv, env);
	*exit_code = 126;
	free(path);
	if (env)
		free_tab(env);
	free_and_exit(root, my_env, exit_code);
}

static void	left_child(t_tree *root, t_tree *node, t_env **my_env,
	int *exit_code)
{
	t_tree	*left_node;

	left_node = node->left;
	if (left_node->type == NODE_PIPE && !left_node->left)
		left_node = left_node->right;
	if (left_node->type == NODE_CMD)
		exec_in_pipe(root, left_node, my_env, exit_code);
	if (left_node->type == NODE_PIPE)
	{
		pipe_orchestrator(root, left_node, my_env, exit_code);
		free_and_exit(root, my_env, exit_code);
	}
}

static void	right_child(t_tree *root, t_tree *node, t_env **my_env,
	int *exit_code)
{
	*exit_code = 0;
	exec_in_pipe(root, node->right, my_env, exit_code);
}

void	pipe_orchestrator(t_tree *root, t_tree *node, t_env **my_env,
	int *exit_code)
{
	int		pipefd[2];
	pid_t	child[2];

	if (pipe(pipefd) == -1)
		*exit_code = errno;
	sig_executing();
	child[0] = fork();
	if (child[0] == -1)
		*exit_code = errno;
	else if (child[0] == 0)
	{
		sig_child();
		pipe_redirections('L', pipefd);
		left_child(root, node, my_env, exit_code);
	}
	child[1] = fork();
	if (child[1] == -1)
		*exit_code = errno;
	else if (child[1] == 0)
	{
		sig_child();
		pipe_redirections('R', pipefd);
		right_child(root, node, my_env, exit_code);
	}
	*exit_code = inspect_child_status(child[1], pipefd, child[0]);
}
