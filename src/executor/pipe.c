/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 23:54:46 by admin             #+#    #+#             */
/*   Updated: 2026/05/03 00:06:18 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void left_child(pid_t *child, int *pipefd, t_tree *node, char **env, t_error_exec *err)
{
	*child = fork();
	if (*child == -1)
	{
		err->err = errno;
		perror("fork");
	}
	if (*child == 0)
	{
		pipe_redirections('L', pipefd);
		child_process(pipefd, node, env, err);		
	}
}

static void right_child(pid_t *child, int *pipefd, t_tree *node, char **env, t_error_exec *err)
{
	*child = fork();
	if (*child == -1)
	{
		err->err = errno;
		perror("fork");
	}
	if (*child == 0)
	{
		pipe_redirections('R', pipefd);
		child_process(pipefd, node, env, err);		
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