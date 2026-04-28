/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:31:07 by admin             #+#    #+#             */
/*   Updated: 2026/04/27 18:36:56 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*prompt;
	t_token	*token;
	t_error	*error;
	t_tree	*tree;

	token = malloc(sizeof(t_token));
	if (!token)
		return (1);
	error = malloc(sizeof(t_error));
	if (!error)
		return (1);
	while (1)
	{
		prompt = readline("minishell>>> ");
		if (!prompt)
			break ;
		if (*prompt)
			add_history(prompt);
		token = lexer_orchestrator(prompt, error);
		tree = parsing_main(token);
		free(prompt);
	}
	printf("%s\n", "minishell>>> exit");
	rl_clear_history();
	return (0);
}

