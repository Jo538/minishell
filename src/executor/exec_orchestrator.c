/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_orchestrator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:23:28 by admin             #+#    #+#             */
/*   Updated: 2026/05/26 02:06:34 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *cmd, char *file, int error)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (error == ERR_CMD)
		ft_putstr_fd("Command not found\n", 2);
	if (error == ERR_CMD_FILE)
		ft_putstr_fd("No such file or directory\n", 2);
	if (!file && error == ERR_PERMISSION)
		ft_putstr_fd("Permission denied\n", 2);
	if (file)
		ft_putstr_fd(file, 2);	
	if (error == ERR_PERMISSION)
		ft_putstr_fd(": Permission denied\n", 2);		
	if (error == ERR_FILE)
		ft_putstr_fd(": No such file or directory\n", 2);
}

static int	translate_errno(int error, int type)
{
	if (error == ENOENT && type == OPEN_FILE)
		return (ERR_FILE);
	if (error == ENOENT && type == OPEN_CMD)
		return (ERR_CMD_FILE);
	if (error == EACCES)
		return (ERR_PERMISSION);
	return (error);
}

static void	set_exit_code(int error, int *exit_code)
{
	if (error == ERR_CMD || error == ERR_CMD_FILE)
		*exit_code = 127;
	if (error == ERR_PERMISSION)
		*exit_code = 126;
	if (error == ERR_FILE || error == ERR_INVALID_IDENTIFIER)
		*exit_code = 1;
	if (error == ERR_NON_NUMERIC_ARGUMENT || error == ERR_TOO_MANY_ARGS)
		*exit_code = 2;
}

void	error_orchestrator(int *exit_code, int translate, int error, int type, char *cmd, char *file)
{
	if (translate == 1)
		error = translate_errno(error, type);
	print_error(cmd, file, error);
	set_exit_code(error, exit_code);	
}

void	executor(t_tree *node, t_env **my_env, int *exit_code)
{
	if (node->type == NODE_CMD)
		cmd_orchestrator(node, my_env, exit_code);
	if (node->type == NODE_PIPE)
		pipe_orchestrator(node, node, my_env, exit_code);
}
