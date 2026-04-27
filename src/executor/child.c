/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:42:39 by admin             #+#    #+#             */
/*   Updated: 2026/04/27 23:20:32 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inspect_child_status(int status)
{
	if (WIFEXITED(status))
		printf("child exited normally with code %d\n", WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		printf("child was killed by signal with code %d\n", WTERMSIG(status));			
}

int	child_orchestrator(t_tree node)
{
	int	fd[2];
	t_error	err;
	int		status;
	pid_t	parent;
	pid_t	child;
	
	err = 0;
	ft_bzero(fd, 2 * sizeof(int));
	if (pipe(fd) == -1)
		perror("pipe");
	child = fork();
	if (child == -1)
		perror("fork");
	if (child == 0)
		child_process(node, &err);
	close(fd[0]);
	close(fd[1]);
	waitpid(child, &status, 0);
	return (inspect_child_status(status));
}
