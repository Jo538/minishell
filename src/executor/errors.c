/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:23:28 by admin             #+#    #+#             */
/*   Updated: 2026/06/04 12:05:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *cmd, char *file, int error)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (error == ERR_CMD)
		ft_putstr_fd("command not found\n", 2);
	if (error == ERR_CMD_FILE)
		ft_putstr_fd("No such file or directory\n", 2);
	if (error == ERR_TOO_MANY_ARGS)
		ft_putstr_fd("Too many arguments\n", 2);
	if (!file && error == ERR_PERMISSION)
		ft_putstr_fd("Permission denied\n", 2);
	if (file)
		ft_putstr_fd(file, 2);
	if (error == ERR_PERMISSION)
		ft_putstr_fd(": Permission denied\n", 2);
	if (error == ERR_FILE)
		ft_putstr_fd(": No such file or directory\n", 2);
	if (error == ERR_INVALID_IDENTIFIER)
		ft_putstr_fd(": Not a valid identifier\n", 2);
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

void	error_orchestrator(int *exit_code, int error, char *cmd, char *file)
{
	print_error(cmd, file, error);
	set_exit_code(error, exit_code);
}

void	error_with_errno(int *exit_code, int type, char *cmd, char *file)
{
	int	error;

	error = translate_errno(errno, type);
	print_error(cmd, file, error);
	set_exit_code(error, exit_code);
}
