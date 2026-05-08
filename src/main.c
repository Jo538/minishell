/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:31:07 by admin             #+#    #+#             */
/*   Updated: 2026/05/08 12:35:59 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdint.h>

// void	print_trees(t_tree *tree);

int	main(void)
{
	char	*prompt;
	t_token	*token;
	t_error	*error;
	t_tree	*tree;
	int		i = -1;

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
		// if (tree)
		// 	print_trees(tree);
		// while (tree->argv[++i])
		printf("Token = %s\n", tree->right->argv[1]);
		// free_the_tree(tree);
		// printf("Token = %s\n", tree->argv[0]);
		// printf("avant expand = %s\n", token->segment->value);
		// token = expand_tokens(token);
		// printf("apres expand = %s\n", token->segment->value);
		i = -1;
		free(prompt);
	}
	free(error);
	free(token);
	printf("%s\n", "minishell>>> exit");
	rl_clear_history();
	return (0);
}

// static char	*get_token_type_str(int type)
// {
// 	if (type == WORD)
// 		return ("WORD");
// 	if (type == PIPE)
// 		return ("PIPE");
// 	if (type == IN_DIR)
// 		return ("IN_DIR");
// 	if (type == OUT_DIR)
// 		return ("OUT_DIR");
// 	if (type == HEREDOC)
// 		return ("HEREDOC");
// 	if (type == APPEND_OUT_DIR)
// 		return ("APPEND_OUT_DIR");
// 	if (type == CMD)
// 		return ("CMD");
// 	return ("UNKNOWN");
// }

// static void	print_tree_right(t_tree *tree, int depth)
// {
// 	if (!tree)
// 		return ;
	
// 	printf("%*s├─ NODE (type=%d: %s)\n", depth * 2, "", tree->type, 
// 		get_token_type_str(tree->type));
	
// 	if (tree->argv && tree->argv[0])
// 		printf("%*s│  └─ cmd: %s\n", depth * 2, "", tree->argv[0]);
	
// 	if (tree->redirections)
// 	{
// 		printf("%*s│  └─ redirections: [présentes mais non affichées]\n", depth * 2, "");
// 		if (tree && tree->right && tree->right->redirections)
// 			printf("%s", tree->right->redirections->file);
// 	}
	
// 	if (tree->right)
// 	{
// 		printf("%*s│\n", depth * 2, "");
// 		printf("%*s└─ RIGHT:\n", depth * 2, "");
// 		print_tree_right(tree->right, depth + 1);
// 	}
// }

// void	print_trees(t_tree *tree)
// {
// 	if (!tree)
// 	{
// 		printf("\nTree is NULL\n");
// 		return ;
// 	}
// 	printf("\n=== TREE RIGHT SIDE ===\n");
// 	print_tree_right(tree, 0);
// 	printf("=== END ===\n\n");
// }

