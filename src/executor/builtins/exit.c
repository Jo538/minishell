/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 18:45:52 by admin             #+#    #+#             */
/*   Updated: 2026/05/21 19:24:20 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_exit(char **cmd, t_error_exec *err)
{
	int	size;

	size = 0;
	while (cmd[size])
		size++;
	if (size > 2)
	{
		err->err = ARG_COUNT;
		err->cmd = ft_strdup("exit");
		return ;		
	}
	// set global var to exit number
	
}