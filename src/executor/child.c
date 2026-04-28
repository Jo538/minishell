/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:42:39 by admin             #+#    #+#             */
/*   Updated: 2026/04/28 20:02:59 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	errors(t_error err)
{
	if (err == 127)
		printf("%s\n", "command not found");
	if (err == ENOENT)
	{
		printf("%s\n", "No such file or directory");
		exit(127);		
	}
	exit(err);
}
static void	child_process(t_tree node, char **env, t_error *err)
{
	char	*path;
	
	path = NULL;
	path = path_orchestrator(node.argv[0], env, err);
	if (!path)
		errors(*err);
	execve(path, node.argv, env);
}

static int	inspect_child_status(pid_t child, int status)
{
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);	
}

int	parent_orchestrator(t_tree node, char **env, t_error *err)
{
	int	fd[2];
	int		status;
	pid_t	child;
	
	child = -1;
	status = -1;
	ft_bzero(fd, 2 * sizeof(int));
	if (pipe(fd) == -1)
	{
		*err = errno;
		perror("pipe");		
	}
	child = fork();
	if (child == -1)
	{
		*err = errno;
		perror("fork");		
	}
	if (child == 0)
		child_process(node, env, err);
	close(fd[0]);
	close(fd[1]);
	return (inspect_child_status(child, status));
}
