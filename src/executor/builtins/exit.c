/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 18:45:52 by admin             #+#    #+#             */
/*   Updated: 2026/06/09 10:34:03 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_arg(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-' || s[0] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	run_exit(char **cmd, int *exit_code)
{
	int	size;

	size = 0;
	while (cmd[size])
		size++;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	if (size >= 2 && !is_numeric_arg(cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		*exit_code = 2;
		return (0);
	}
	if (size > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		*exit_code = 1;
		return (1);
	}
	if (size == 2)
		*exit_code = (unsigned char)ft_atoi(cmd[1]);
	return (0);
}
