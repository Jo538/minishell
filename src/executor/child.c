/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:42:39 by admin             #+#    #+#             */
/*   Updated: 2026/05/03 00:07:57 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	errors(t_error_exec *err)
{
	if (err->err == 127)
		printf("%s\n", "command not found");
	if (err->err == ENOENT)
	{
		printf("%s\n", "No such file or directory");
		if (err->operation == CMD_OPE)
			exit(127);	
		if (err->operation == OPEN_OPE)
			exit(1);		
	}
	if (err->err == EACCES)
	{
		printf("%s\n", "Permission denied");
		if (err->operation == CMD_OPE)
			exit(126);	
		if (err->operation == OPEN_OPE)
			exit(1);	
	}
	exit(err->err);
}

void	pipe_redirections(char direction, int *pipefd)
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

void	child_process(int *pipefd, t_tree *node, char **env, t_error_exec *err)
{
	char	*path;
	
	path = NULL;
	files_redirections_orchestrator(pipefd, node->redirections, err);
	if (err->err)
		errors(err);
	path = path_orchestrator(node->argv[0], env, err);
	if (!path)
		errors(err);
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

int	cmd_orchestrator(t_tree *node, char **env, t_error_exec *err)
{
	int		status;
	pid_t	child;
	
	child = -1;
	status = -1;
	child = fork();
	if (child == -1)
	{
		err->err = errno;
		perror("fork");		
	}
	if (child == 0)
		child_process(NULL, node, env, err);
	return (inspect_child_status(child, status));
}
