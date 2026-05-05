/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 23:54:46 by admin             #+#    #+#             */
/*   Updated: 2026/05/05 15:35:39 by admin            ###   ########.fr       */
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

static void left_child(pid_t *child, int *pipefd, t_tree *node, char **env, t_error_exec *err)
{
	char	*path;
	
	path = NULL;
	*child = fork();
	if (*child == -1)
	{
		err->err = errno;
		perror("fork");
	}
	if (*child == 0)
	{
		if (node->type == NODE_CMD)
		{
			files_redirections_orchestrator(pipefd, node->redirections, err);
			if (err->err)
				errors(pipefd, err);
			path = path_orchestrator(node->argv[0], env, err);
			if (!path)
				errors(pipefd, err);
			pipe_redirections('L', pipefd);
			execve(path, node->argv, env);
			err->err = errno;
			errors(pipefd, err);				
		}
		if (node->type == NODE_PIPE)
		{
			pipe_redirections('L', pipefd);
			exit(pipe_orchestrator(node, env, err));			
		}
	}
}

static void right_child(pid_t *child, int *pipefd, t_tree *node, char **env, t_error_exec *err)
{
	char	*path;
	
	path = NULL;
	*child = fork();
	if (*child == -1)
	{
		err->err = errno;
		perror("fork");
	}
	if (*child == 0)
	{
		files_redirections_orchestrator(pipefd, node->redirections, err);
		if (err->err)
			errors(pipefd, err);
		path = path_orchestrator(node->argv[0], env, err);
		if (!path)
			errors(pipefd, err);
		pipe_redirections('R', pipefd);
		execve(path, node->argv, env);
		err->err = errno;
		errors(pipefd, err);	
	}
}

int	pipe_orchestrator(t_tree *node, char **env, t_error_exec *err)
{
	int		status;
	int		pipefd[2];
	pid_t	child[2];
	
	ft_bzero(child, 2 * sizeof(pid_t));
	ft_bzero(pipefd, 2 * sizeof(int));
	status = -1;

	if (pipe(pipefd) == -1)
	{
		err->err = errno;
		perror("pipe");		
	}
	left_child(&child[0], pipefd, node->left, env, err);
	right_child(&child[1], pipefd, node->right, env, err);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(child[0], NULL, 0);
	return (inspect_child_status(child[1], status));
}
