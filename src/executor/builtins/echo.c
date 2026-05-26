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

static void	setup(char **cmd, int *i, int *n_flag)
{
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
	{
		*i = 2;
		*n_flag = 1;
	}
	else
	{
		*i = 1;
		*n_flag = 0;
	}
}

void	run_echo(char **cmd)
{
	int	i;
	int n_flag;
	
	setup(cmd, &i, &n_flag);
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (!cmd[i])
			break ;
		printf("%c", ' ');	
	}
	if (n_flag == 0)
	{
		printf("%c", '\n');
		return ;			
	}
}
