/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:42:39 by admin             #+#    #+#             */
/*   Updated: 2026/05/18 15:11:22 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors(int *pipefd, t_error_exec *err)
{
	ft_putstr_fd(err->cmd, 2);
	if (err->err == 127)
		ft_putendl_fd(": Command not found", 2);
	if (err->err == ENOENT)
	{
		ft_putendl_fd(": No such file or directory", 2);
		if (err->operation == OPEN_CMD)
			exit(127);	
		if (err->operation == OPEN_FILE)
			exit(1);		
	}
	if (err->err == EACCES)
	{
		ft_putendl_fd(": Permission denied", 2);
		if (err->operation == OPEN_CMD)
			exit(126);	
		if (err->operation == OPEN_FILE)
			exit(1);	
	}
	exit(err->err);
}

void	child_process(int *pipefd, t_tree *node, char **env, t_error_exec *err)
{
	char	*path;
	
	path = NULL;
	files_redirections_orchestrator(pipefd, node->redirections, err);
	if (err->err)
		errors(pipefd, err);
	path = path_orchestrator(node->argv[0], env, err);
	if (!path)
		errors(pipefd, err);
	execve(path, node->argv, env);
	err->err = errno;
	errors(pipefd, err);	
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
