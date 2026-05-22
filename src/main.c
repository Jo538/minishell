/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:31:07 by admin             #+#    #+#             */
/*   Updated: 2026/05/23 01:48:20 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdint.h>

int	main(char **env)
{
	int		exit_code;
	t_env	**my_env;
	char	*prompt;
	t_token	*token;
	t_tree	*tree;
	int		i = -1;

	my_env = create_env(env, &exit_code);
	if (exit_code == ERR_FATAL)
		return (ERR_FATAL);
	while (1)
	{
		prompt = readline("minishell>>> ");
		if (!prompt)
			break ;
		if (*prompt)
			add_history(prompt);
		token = lexer(prompt, &exit_code);
		free(prompt);
		if (exit_code = ERR_FATAL)
			return (exit_code);
		tree = parsing_main(token);
		free_token_list(token);
		// expander
		free_the_tree(tree, token); //necessite d etre fait avant le free des tokens ou alors besoin d envoyer l info de have_pipe a la place de token
		executor(tree, my_env, &exit_code);
	}
	free(token);
	printf("%s\n", "minishell>>> exit");
	rl_clear_history();
	return (0);
}
