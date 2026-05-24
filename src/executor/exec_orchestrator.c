/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_orchestrator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:23:28 by admin             #+#    #+#             */
/*   Updated: 2026/05/24 01:32:40 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd, char *file, int error)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (error == ERR_CMD)
		ft_putstr_fd("Command not found\n", 2);
	if (error == ERR_CMD_FILE)
		ft_putstr_fd("No such file or directory\n", 2);
	if (error == ERR_PERMISSION)
		ft_putstr_fd("Permission denied\n", 2);
	if (error == ENOENT)
		ft_putstr_fd("No such file or directory\n", 2);
	if (error == EACCES)
	{
		ft_putstr_fd(file, 2);	
		ft_putstr_fd(": Permission denied\n", 2);		
	}
}

void	executor(t_tree *node, t_env **my_env, int *exit_code)
{
	if (node->type == NODE_CMD)
		cmd_orchestrator(node, my_env, exit_code);
	if (node->type == NODE_PIPE)
		pipe_orchestrator(node, my_env, exit_code);
}
