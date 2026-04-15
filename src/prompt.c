/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:28:42 by benji             #+#    #+#             */
/*   Updated: 2026/04/15 14:29:40 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sig(int sig)
{
	if (sig == SIGQUIT)
		(void)sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*prompt_minishell(void)
{
	struct sigaction	set;
	char				*mess;

	sigemptyset(&set.sa_mask);
	set.sa_flags = 0;
	set.sa_handler = handler_sig;
	sigaction(SIGINT, &set, NULL);
	sigaction(SIGQUIT, &set, NULL);
	mess = readline("minishell>>> ");
	if (!mess)
	{
		printf("exit\n");
		exit(0);
	}
	return (mess);
}
