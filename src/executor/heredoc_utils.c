/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:37:56 by bribot            #+#    #+#             */
/*   Updated: 2026/06/11 12:04:31 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ls	init_ls(char *delim)
{
	t_ls	ls;

	ls.delim = delim;
	ls.saved_stdin = dup(STDIN_FILENO);
	ls.saved_stdout = dup(STDOUT_FILENO);
	ls.tty_fd = open("/dev/tty", O_WRONLY);
	return (ls);
}
