/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:00:21 by benji             #+#    #+#             */
/*   Updated: 2026/04/07 13:30:47 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// have a open quote fonctionne de facon binaire : si il y a ' ouvert cela renvoie 1, " cela renvoie 2 et ' + " cela renvoie 3, 
// cela sera pratique pour attendre qu elles se ferment

int	have_a_open_quote(char *str)
{
	int	i;
	int	number_one;
	int	number_two;

	if (!str)
		return (0);
	number_one = 0;
	number_two = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 39)
			number_one++;
		if (str[i] == 34)
			number_two++;
	}
	i = 0;
	if (number_one % 2 == 1)
		i += 1;
	if (number_two % 2 == 1)
		i += 2;
	return (i);
}

char*	prompt(void)
{
	char	*mess;
	char	*tmp;

	if (!isatty(0))
		return (NULL);
	mess = readline("mimnishell>>>");
	if (!mess)
		return (NULL);
	while (have_a_open_quote(mess))
	{
		tmp = readline(""); //peut etre rajouter un if return NULL
		mess = ft_strjoin(mess, "\n");
		mess = ft_strjoin(mess, tmp);
	}
	add_history(mess);
	return(mess);
}
