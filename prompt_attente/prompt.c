/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:00:21 by benji             #+#    #+#             */
/*   Updated: 2026/04/11 13:07:14 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static volatile sig_atomic_t g_sig;

// have a open quote fonctionne de facon binaire : si il y a ' ouvert cela renvoie 1, " cela renvoie 2 et ' + " cela renvoie 3, 
// cela sera pratique pour attendre qu elles se ferment

void	handler(int sig, siginfo_t *info, void *s)
{
	(void)s;
	(void)info;
	// if (sig == SIGQUIT)
	// {
	// }
	if (sig == SIGINT) //change de ligne et remet le prompt minishell>>>
	{
		g_sig = 1;
		write(1, "\n", 1);
		rl_replace_line("", 1); 
		rl_on_new_line();
		rl_redisplay();
	}
}

int	have_a_open_quote(char *str) //verifie si une quote est ouverte en prenant en compte les cas de "  ahdg ' ajerh" comme ferme
{
	int	i;
	int	who_open;

	if (!str)
		return (0);
	i = -1;
	who_open = 0;
	while (str[++i])
	{
		if (who_open != 0 && who_open == str[i])
			who_open = 0;
		else if ((str[i] == 34 || str[i] == 39) && who_open == 0)
			who_open = str[i];
	}
	return (who_open);
}

char	*prompt(void)
{
	char				*mess;
	struct sigaction	set;

	g_sig = 0;
	set.sa_flags = SA_SIGINFO;
	sigemptyset(&set.sa_mask);
	set.sa_sigaction = handler;
	sigaction(SIGINT, &set, NULL); // prepare le signal SIGINT
	if (!isatty(0))
		return (NULL);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	mess = readline("minishell>>>"); //affiche minishell>>> et attend une entre (n a pas de fonctions pour le stoper, mais peut etre faisable avec ioctl)
	if (!mess)
		return (NULL);
	if (have_a_open_quote(mess))
		return (handle_quotes(mess)); //rentre dans la fonction qui gere les open quotes	
	add_history(mess);
	return (mess);
}
