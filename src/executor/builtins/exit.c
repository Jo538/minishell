/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 18:45:52 by admin             #+#    #+#             */
/*   Updated: 2026/05/26 17:01:47 by admin            ###   ########.fr       */
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

void	run_exit(char **cmd, int *exit_code)
{
	int	size;

	size = 0;
	while (cmd[size])
		size++;
	ft_putstr_fd("exit\n", 2);
	if (size >= 2 && !is_numeric_arg(cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (size > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		*exit_code = 1;
		return ;
	}
	if (size == 2)
		exit((unsigned char)ft_atoi(cmd[1]));
	exit((unsigned char)*exit_code);
}
