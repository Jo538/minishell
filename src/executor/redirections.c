/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:07:00 by admin             #+#    #+#             */
/*   Updated: 2026/06/08 14:37:50 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc(t_redir *redir, int *error)
{
	int	fd;
	int	interrupted;

	fd = open("temp_heredoc.txt", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
		return (-1);
	interrupted = read_heredoc_into(fd, redir->file);
	close(fd);
	if (interrupted)
	{
		unlink("temp_heredoc.txt");
		*error = -1;
		return (-1);
	}
	fd = open("temp_heredoc.txt", O_RDONLY);
	unlink("temp_heredoc.txt");
	return (fd);
}

static int	open_redirection_file(t_redir *redir, int *error)
{
	int	fd;

	fd = -1;
	if (redir->type == IN_DIR)
		fd = open(redir->file, O_RDONLY);
	if (redir->type == OUT_DIR)
		fd = open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (redir->type == APPEND_OUT_DIR)
		fd = open(redir->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (redir->type == HEREDOC)
		fd = open_heredoc(redir, error);
	if (fd == -1 && *error != -1)
		*error = errno;
	return (fd);
}

static void	run_redirection(int fd, t_redir *redir)
{
	if (redir->type == IN_DIR || redir->type == HEREDOC)
	{
		dup2(fd, 0);
		close(fd);
	}
	if (redir->type == OUT_DIR || redir->type == APPEND_OUT_DIR)
	{
		dup2(fd, 1);
		close(fd);
	}
}

static int	same_redirection_later(t_redir *redir)
{
	int	type;

	type = redir->type;
	redir = redir->next;
	while (redir)
	{
		if (redir->type == type)
			return (1);
		redir = redir->next;
	}
	return (0);
}

void	files_redirections_orchestrator(char *cmd, int *pipefd,
	t_redir *redir, int *exit_code)
{
	int	error;
	int	fd;

	(void)pipefd;
	if (!redir)
		return ;
	while (redir)
	{
		error = 0;
		fd = open_redirection_file(redir, &error);
		if (fd == -1 && error == -1)
		{
			*exit_code = 130;
			return ;
		}
		if (fd == -1)
			return (error_with_errno(exit_code, OPEN_FILE, cmd, redir->file));
		if (!same_redirection_later(redir))
			run_redirection(fd, redir);
		else
			close(fd);
		redir = redir->next;
	}
}
