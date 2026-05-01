/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:07:00 by admin             #+#    #+#             */
/*   Updated: 2026/05/01 15:39:09 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirection_error(int *pipefd, t_redir *redir, t_error_exec *err)
{
	close(pipefd[0]);
	close(pipefd[1]);
	err->err = errno;
	err->operation = OPEN_OPE;
}

static int	check_for_redirections(int *pipefd, t_redir *redir)
{
	if (redir == NULL)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (0);
	}
	return (1);
}

static int	open_redirection_file(int *pipefd, t_redir *redir, t_error_exec *err)
{
	int	fd;

	if (redir->type == IN_DIR)
		fd = open(redir->file, O_RDONLY);
	if (redir->type == OUT_DIR)
		fd = open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	return (fd);
}

static void	run_redirection(int fd, int *pipefd, t_redir *redir)
{
	if (redir->type == IN_DIR)
	{
		dup2(fd, 0);
		close(fd);
		close(pipefd[0]);
	}
	if (redir->type == OUT_DIR)
	{
		dup2(fd, 1);
		close(fd);
		close(pipefd[1]);
	}
}

static int	check_same_redirection_later(t_redir *redir)
{
	int	type;

	
}

void	redirections_orchestrator(int *pipefd, t_redir *redir, t_error_exec *err)
{
	int	fd;

	if (!check_for_redirections(pipefd, redir))
		return ;
	
	while (redir)
	{
		fd = open_redirection_file(pipefd, redir, err);
		if (fd == -1)
			return (redirection_error(pipefd, redir, err));
		if (!redir->next)
		{
			run_redirection(fd, pipefd, redir);
			return ;
		}
		else if (redir->next && redir->next->type != redir->type)
			run_redirection(fd, pipefd, redir);
		else
			close(fd);
		redir = redir->next;
	}
}