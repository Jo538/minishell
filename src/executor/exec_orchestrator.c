/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_orchestrator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:23:28 by admin             #+#    #+#             */
/*   Updated: 2026/05/23 01:50:33 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_tree *node, t_env **my_env, int *exit_code)
{
	if (node->type == NODE_CMD)
		cmd_orchestrator(node, my_env, exit_code);
	pipe_orchestrator(node, my_env, exit_code);
}
