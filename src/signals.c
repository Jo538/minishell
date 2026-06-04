/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:55:31 by admin             #+#    #+#             */
/*   Updated: 2026/06/04 12:01:54 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sig(int sig)
{
	if (sig == SIGQUIT)
	{
		rl_redisplay();
		g_signum = SIG_QUIT;
	}
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signum = SIG_INT;
	}
}

void	sig_init(void)
{
	struct sigaction	set;

	g_signum = NO_SIG;
	sigemptyset(&set.sa_mask);
	set.sa_flags = 0;
	set.sa_handler = handler_sig;
	sigaction(SIGINT, &set, NULL);
	sigaction(SIGQUIT, &set, NULL);
}