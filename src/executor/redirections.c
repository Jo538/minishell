/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 13:07:00 by admin             #+#    #+#             */
/*   Updated: 2026/05/03 12:33:11 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirection_error(int *pipefd, t_redir *redir, t_error_exec *err)
{
	if (pipefd)
	{
		close(pipefd[0]);
		close(pipefd[1]);		
	}
	err->err = errno;
	err->operation = OPEN_OPE;
	err->cmd = redir->file;
}

static int	open_redirection_file(t_redir *redir, t_error_exec *err)
{
	int	fd;
	int	len;

	len = 0;
	if (redir->type == IN_DIR)
		fd = open(redir->file, O_RDONLY);
	if (redir->type == OUT_DIR)
		fd = open(redir->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (redir->type == APPEND_OUT_DIR)
		fd = open(redir->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (redir->type == HEREDOC)
	{
		len = ft_strlen(redir->file);
		fd = open("temp_heredoc.txt", O_CREAT | O_RDWR, 0644);
		write(fd, redir->file, len);
		close(fd);
		fd = open("temp_heredoc.txt", O_RDWR);
		unlink("temp_heredoc.txt");	
	}
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

static int	check_same_redirection_later(t_redir *redir)
{
	int	type;

	type = redir->type;
	redir = redir->next;
	while (redir)
	{
		if (redir-> type == type)
			return (1);
		redir = redir->next;
	}
	return (0);
}

void	files_redirections_orchestrator(int *pipefd, t_redir *redir, t_error_exec *err)
{
	int	fd;
	int	flag;

	flag = 0;
	if (!redir)
		return ;
	while (redir)
	{
		fd = open_redirection_file(redir, err);
		if (fd == -1)
			return (redirection_error(pipefd, redir, err));
		if (!redir->next)
		{
			run_redirection(fd, redir);
			return ;
		}
		flag = check_same_redirection_later(redir);
		if (!flag)
			run_redirection(fd, redir);
		else
			close(fd);
		flag = 0;
		redir = redir->next;
	}
}
