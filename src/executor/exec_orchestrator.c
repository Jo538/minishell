/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_orchestrator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:23:28 by admin             #+#    #+#             */
/*   Updated: 2026/05/05 21:49:26 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_tree *node, char **env)
{
	t_error_exec	err;

	ft_bzero(&err, sizeof(t_error_exec));
	if (node->type == NODE_CMD)
		return (cmd_orchestrator(node, env, &err));
	return (pipe_orchestrator(node, env, &err));
}
