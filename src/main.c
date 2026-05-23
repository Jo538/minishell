/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:31:07 by admin             #+#    #+#             */
/*   Updated: 2026/05/22 14:08:41 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdint.h>

int	main(void)
{
	char	*prompt;
	t_token	*token;
	t_error	*error;
	t_tree	*tree;
	int		i = 0;

	error = malloc(sizeof(t_error));
	if (!error)
		return (1);
	while (1)
	{
		i = 0;
		prompt = readline("minishell>>> ");
		if (!prompt)
			break ;
		if (*prompt)
			add_history(prompt);
		// prompt = ft_strdup("asdsdkuhj | akj | askjdaksdjh | akjsdhhj | kjh | ksjad < askjd"); // dequote cette ligne pour enlever tout les leaks lier a readline
		token = lexer_orchestrator(prompt, error);
		// printf("%s\n", token->segment->value);
		printf("bon ou pas = %d\n", check_ifgood(token));
		// return (0);
		// printf("token = %s\n", token->next->next->next->segment->value);
		// tree = parsing_main(token); // ICI
		// while (tree->right->redirections)
		// {
		// 	printf("redir = %s\n", tree->right->redirections->file);
		// 	tree->right->redirections = tree->right->redirections->next;
		// }
		// printf("%s\n", tree->argv);
		// while (tree->argv[i])
		// 	printf("av = %s\n", tree->argv[i++]);
		// free_the_tree(tree, token); //necessite d etre fait avant le free des tokens ou alors besoin d envoyer l info de have_pipe a la place de token
		free(prompt);
	}
	free(error);
	free(token);
	printf("%s\n", "minishell>>> exit");
	rl_clear_history();
	return (0);
}
