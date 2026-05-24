/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 23:54:46 by admin             #+#    #+#             */
/*   Updated: 2026/05/24 01:39:43 by admin            ###   ########.fr       */
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

static void left_child(int *pipefd, t_tree *node, t_env **my_env, int *exit_code)
{
	char	**env;
	char	*path;

	path = NULL;
	if (node->type == NODE_CMD)
	{
		files_redirections_orchestrator(node->argv[0], pipefd, node->redirections, exit_code);
		if (*exit_code)
			errors(exit_code);
		path = path_orchestrator(node->argv[0], my_env, exit_code);
		if (!path)
			errors(exit_code);
		pipe_redirections('L', pipefd);
		env = consolidate_my_env(my_env, exit_code);
		execve(path, node->argv, env);			
	}
	if (node->type == NODE_PIPE)
	{
		pipe_redirections('L', pipefd);
		pipe_orchestrator(node, my_env, exit_code);
		exit(0);		
	}
}

static void right_child(int *pipefd, t_tree *node, t_env **my_env, int *exit_code)
{
	char	**env;
	char	*path;
	
	path = NULL;
	files_redirections_orchestrator(node->argv[0], pipefd, node->redirections, exit_code);
	if (*exit_code)
		errors(exit_code);
	path = path_orchestrator(node->argv[0], my_env, exit_code);
	if (!path)
		errors(exit_code);
	pipe_redirections('R', pipefd);
	env = consolidate_my_env(my_env, exit_code);
	execve(path, node->argv, env);
	*exit_code = errno;
	errors(exit_code);	
}

void	pipe_orchestrator(t_tree *node, t_env **my_env, int *exit_code)
{
	int		status;
	int		pipefd[2];
	pid_t	child[2];
	
	ft_bzero(child, 2 * sizeof(pid_t));
	ft_bzero(pipefd, 2 * sizeof(int));
	status = -1;

	if (pipe(pipefd) == -1)
		*exit_code= errno;	
	child[0] = fork();
	if (child[0] == -1)
		*exit_code= errno;
	else if (child[0] == 0)
		left_child(pipefd, node->left, my_env, exit_code);
	child[1] = fork();
	if (child[1] == -1)
		*exit_code = errno;
	else if (child[1] == 0)
		right_child(pipefd, node->right, my_env, exit_code);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child[0], NULL, 0);
	inspect_child_status(child[1], status);
}
