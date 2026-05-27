/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 18:27:31 by admin             #+#    #+#             */
/*   Updated: 2026/05/21 18:30:29 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_env(char **cmd, t_env **my_env, int *exit_code)
{
	int	i;

	if (cmd[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		*exit_code = 127;
		return ;
	}
	i = 0;
	while (my_env[i])
	{
		if (my_env[i]->export_flag && my_env[i]->set_flag)
			printf("%s=%s\n", my_env[i]->key, my_env[i]->value);
		i++;
	}
}
