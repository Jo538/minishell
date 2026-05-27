/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 15:54:56 by admin             #+#    #+#             */
/*   Updated: 2026/05/17 16:57:09 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *s)
{
	int	i;

	if (s[0] != '-' || !s[1])
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

void	run_echo(char **cmd)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	while (cmd[i] && is_n_flag(cmd[i]))
	{
		n_flag = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}
