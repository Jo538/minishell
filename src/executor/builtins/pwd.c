/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:18:01 by admin             #+#    #+#             */
/*   Updated: 2026/05/27 15:24:56 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pwd(void)
{
	char	buffer[4096];

	ft_bzero(buffer, sizeof(buffer));
	if (getcwd(buffer, sizeof(buffer) - 1))
		printf("%s\n", buffer);
}
