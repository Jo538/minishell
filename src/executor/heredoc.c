/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:00:00 by admin             #+#    #+#             */
/*   Updated: 2026/06/11 12:00:49 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signum = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

void	sig_heredoc(struct sigaction *old_int, struct sigaction *old_quit)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = handler_heredoc;
	sigaction(SIGINT, &act, old_int);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, old_quit);
}

static int	process_heredoc_line(t_ls ls, int fd,
					int heredoc_quoted, t_envexit envexit)
{
	size_t	dlen;

	if (g_signum == SIGINT)
	{
		if (ls.line)
			free(ls.line);
		return (1);
	}
	if (!ls.line)
		return (2);
	dlen = ft_strlen(ls.delim);
	if (ft_strlen(ls.line) == dlen && ft_strncmp(ls.line, ls.delim, dlen) == 0)
	{
		free(ls.line);
		return (2);
	}
	if (!heredoc_quoted)
	{
		ls.line = expand_segtrot(ls.line, envexit.my_env, envexit.exit_code);
		if (!ls.line)
			return (*envexit.exit_code = ERR_FATAL, 1);
	}
	write(fd, ls.line, ft_strlen(ls.line));
	write(fd, "\n", 1);
	return (free(ls.line), 0);
}

static void	restore_term_and_stdin(int saved_stdin, struct termios *saved_term)
{
	dup2(saved_stdin, STDIN_FILENO);
	tcsetattr(STDIN_FILENO, TCSANOW, saved_term);
}

int	read_heredoc_into(int fd, char *delim,
				int heredoc_quoted, t_envexit envexit)
{
	struct sigaction	old[2];
	struct termios		saved_term;
	t_ls				ls;

	ls = init_ls(delim);
	tcgetattr(ls.saved_stdin, &saved_term);
	if (ls.tty_fd != -1)
	{
		dup2(ls.tty_fd, STDOUT_FILENO);
		close(ls.tty_fd);
	}
	sig_heredoc(&old[0], &old[1]);
	ls.res = 0;
	while (ls.res == 0)
	{
		ls.line = readline("> ");
		ls.res = process_heredoc_line(ls, fd,
				heredoc_quoted, envexit);
	}
	dup2(ls.saved_stdout, STDOUT_FILENO);
	close(ls.saved_stdout);
	if (ls.res == 1)
		restore_term_and_stdin(ls.saved_stdin, &saved_term);
	return (close(ls.saved_stdin), sigaction(SIGINT, &old[0], NULL),
		sigaction(SIGQUIT, &old[1], NULL), ls.res == 1);
}
