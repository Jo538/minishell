/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:31:07 by admin             #+#    #+#             */
/*   Updated: 2026/04/14 15:13:48 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("minishell>>> ");
		if (!prompt)
			break ;
		add_history(prompt);
		free(prompt);
	}
	clear_history();
	return (0);
}
