/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:21:33 by benji             #+#    #+#             */
/*   Updated: 2026/04/11 13:19:24 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static volatile sig_atomic_t g_sig;

void	handler_sig_quotes(int sig, siginfo_t *info, void *s)
{
	(void)info;
	(void)s;
	// if (sig == SIGQUIT)
	// {
		
	// }
	if (sig == SIGINT) //c est ca qui ne fonctionne pas
	{
		g_sig = 1;
		// char c = '\n';
		// ioctl(STDIN_FILENO, TIOCSTI, &c);
		// usleep(15);
		write(1, "\n", 1);
		prompt();
	}
}

char	*handle_quotes(char *mess)
{
	char				*tmp;
	struct sigaction	set;

	g_sig = 0;
	set.sa_flags = SA_SIGINFO;
	sigemptyset(&set.sa_mask);
	set.sa_sigaction = handler_sig_quotes;
	sigaction(SIGINT, &set, NULL); //gere les SIGINT
	sigaction(SIGQUIT, &set, NULL); //je ne comprend pas pourquoi ca fait quelque chose alors qu il n est dans aucun code
	while (have_a_open_quote(mess) || g_sig == 1)
	{
		if (g_sig == 1)
			return (free(mess), NULL);
		tmp = readline(">");
		mess = ft_strjoin(mess, "\n");
		mess = ft_strjoin(mess, tmp);
		free(tmp); // ce mini programme tourne tant qu il y a une open quotes ou qu aucun signal n q ete presse, 
	}
	add_history(mess);
	return (mess);
}
