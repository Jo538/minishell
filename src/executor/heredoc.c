/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 14:00:00 by admin             #+#    #+#             */
/*   Updated: 2026/06/09 14:00:00 by admin            ###   ########.fr       */
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

static int	process_heredoc_line(char *line, int fd, char *delim)
{
	size_t	dlen;

	if (g_signum == SIGINT)
	{
		if (line)
			free(line);
		return (1);
	}
	if (!line)
		return (2);
	dlen = ft_strlen(delim);
	if (ft_strlen(line) == dlen && ft_strncmp(line, delim, dlen) == 0)
	{
		free(line);
		return (2);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (0);
}

static void	restore_term_and_stdin(int saved_stdin, struct termios *saved_term)
{
	dup2(saved_stdin, STDIN_FILENO);
	tcsetattr(STDIN_FILENO, TCSANOW, saved_term);
}

int	read_heredoc_into(int fd, char *delim)
{
	struct sigaction	old[2];
	struct termios		saved_term;
	char				*line;
	int					saved_stdin;
	int					res;

	saved_stdin = dup(STDIN_FILENO);
	tcgetattr(saved_stdin, &saved_term);
	sig_heredoc(&old[0], &old[1]);
	res = 0;
	while (res == 0)
	{
		line = readline("> ");
		res = process_heredoc_line(line, fd, delim);
	}
	if (res == 1)
		restore_term_and_stdin(saved_stdin, &saved_term);
	close(saved_stdin);
	sigaction(SIGINT, &old[0], NULL);
	sigaction(SIGQUIT, &old[1], NULL);
	return (res == 1);
}
