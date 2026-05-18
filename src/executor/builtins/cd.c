/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 17:04:28 by admin             #+#    #+#             */
/*   Updated: 2026/05/18 16:15:43 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cd(char **cmd, t_error_exec *err)
{
	int	res;

	res = chdir(cmd[1]);
	if (res == -1)
	{
		err->err = errno;
		err->operation = OPEN_FILE;
		err->cmd = cmd[1];
	}
}
