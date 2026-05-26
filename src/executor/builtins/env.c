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

void	run_env(t_env **my_env)
{
	int	i;

	i = 0;
	while(my_env[i])
	{
		if (my_env[i]->export_flag && my_env[i]->set_flag)
			printf("%s=%s\n", my_env[i]->key, my_env[i]->value);
		i++;
	}
}