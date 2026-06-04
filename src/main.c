/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:31:07 by admin             #+#    #+#             */
/*   Updated: 2026/06/04 11:13:30 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	**run_one_line(char *prompt, t_env **my_env, int *exit_code)
{
	t_token	*token;
	t_tree	*tree;

	token = lexer(prompt, exit_code);
	if (*exit_code == ERR_FATAL || !token)
		return (my_env);
	if (check_ifgood(token))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		*exit_code = 2;
		return (free_token_list(token), my_env);
	}
	tree = parsing_main(token, my_env, exit_code); // qjouter env et exitcode
	if (!tree)
		return (free_token_list(token), my_env);
	my_env = executor(tree, my_env, exit_code);
	free_the_tree(tree, token);
	free_token_list(token);
	return (my_env);
}

int	main(int argc, char **argv, char **envp)
{
	int		exit_code;
	t_env	**my_env;
	char	*prompt;

	(void)argc;
	(void)argv;
	exit_code = 0;
	my_env = create_env(envp, &exit_code);
	while (1)
	{
		prompt = readline("minishell>>> ");
		if (!prompt)
			break ;
		if (*prompt)
			add_history(prompt);
		my_env = run_one_line(prompt, my_env, &exit_code);
		free(prompt);
		if (exit_code == ERR_FATAL)
			break ;
	}
	printf("minishell>>> exit\n");
	rl_clear_history();
	free_my_env(my_env);
	return (exit_code);
}
