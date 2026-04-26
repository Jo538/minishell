/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_orchestrator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 09:43:08 by admin             #+#    #+#             */
/*   Updated: 2026/04/27 01:16:43 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	helper_free_token_list(t_token *token)
{
	int i = 0;
	t_segment *segment;

	while (i < 3)
	{
		if (i == 0)
		{
			segment = ft_calloc(1, sizeof(t_segment));
			token->segment = segment;
		}
		else 
		{
			segment->next = ft_calloc(1, sizeof(t_segment));
			segment = segment->next;
		}
		segment->value = ft_calloc(1, 3);
		i++;	
	}
}

void	test_free_token_list(void)
{
	int	i = 0;
	t_token	*head;
	t_token	*token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return ;
	while (i < 3)
	{
		if (i > 0)
		{
			token->next = ft_calloc(1, sizeof(t_token));
			token = token->next;			
		}
		if (i == 0)
			head = token;
		helper_free_token_list(token);
		i++;	
	}
	free_token_list(head);
}

static void	helper_test_lexer_orchestrator(char *prompt, t_token *actual, t_test_case test_case)
{
	int i = 0;
	int j = 0;
	t_test_token *token = test_case.expected_tokens;
	t_segment *segment;
	
	if (actual)
		segment = actual->segment;
	while (i < test_case.num_token)
	{
		if (test_case.num_token == 0 && !actual)
			break ;
		if (actual->type != test_case.expected_tokens[i].token_type)
			printf("--FAIL TYPE-- %s\nactual: %d\nexpected: %d\n", prompt, actual->type, test_case.expected_tokens[i].token_type);
		j = 0;
		while (j < test_case.expected_tokens[i].count_segment)
		{
			if (strcmp(segment->value, test_case.expected_tokens[i].segment[j].value) != 0)
				printf("--FAIL VALUE-- %s\nactual: %s\nexpected: %s\n", prompt, segment->value, test_case.expected_tokens[i].segment[j].value);
			if (segment->quote_type != test_case.expected_tokens[i].segment[j].quoting_type)
				printf("--FAIL QUOTE-- %s\nactual: %d\nexpected: %d\n", prompt, segment->quote_type, test_case.expected_tokens[i].segment[j].quoting_type);
			segment = segment->next;
			j++;	
		}
		actual = actual->next;
		if (actual)
			segment = actual->segment;
		i++;	
	}
	printf("--SUCCESS-- %s\n", prompt);
}

void	test_lexer_orchestrator(void)
{
	int i = 0;
	t_error err = 0;
	t_token *actual;
	char *prompt[] = {
		"echo hello",
		"echo helloworld",
		"echo hello\"world\"",
		"echo      hello",
		"echo > in.txt",
		"echo >> in.txt",
		"echo >>> in.txt",
		"echo>>> in.txt",
		"hel'lo wo'rld",
		"echo|hi",
		"\"\"",
		"",
		"     ",
		"\'\'",
		" ''",
		"\"<\"",
		"|",
		"<<",
		">\"file\"",
		"\"echo\"|cat",
		"\"hello\"'world'",
		"'hello'\"world\"",
		"hello'world'",
		"'hello'world",
		"'hi\"Bob'"
	};

	t_test_case test_case[] = {
		{2, (t_test_token[]){{WORD, 1, &(t_test_segment){"echo", UNQUOTED}}, {WORD, 1, &(t_test_segment){"hello", UNQUOTED}}}},
		{2, (t_test_token[]){{WORD, 1, &(t_test_segment){"echo", UNQUOTED}}, {WORD, 1, &(t_test_segment){"helloworld", UNQUOTED}}}},
		{2, (t_test_token[]){{WORD, 1, &(t_test_segment){"echo", UNQUOTED}}, {WORD, 2, (t_test_segment[]){{"hello", UNQUOTED}, {"world", D_QUOTED}}}}},
		{2, (t_test_token[]){{WORD, 1, &(t_test_segment){"echo", UNQUOTED}}, {WORD, 1, &(t_test_segment){"hello", UNQUOTED}}}},
		{3, (t_test_token[]){{WORD, 1, &(t_test_segment){"echo", UNQUOTED}}, {OUT_DIR, 1, &(t_test_segment){">", UNQUOTED}}, {WORD, 1, &(t_test_segment){"in.txt", UNQUOTED}}}},
		{3, (t_test_token[]){{WORD, 1, &(t_test_segment){"echo", UNQUOTED}}, {APPEND_OUT_DIR, 1, &(t_test_segment){">>", UNQUOTED}}, {WORD, 1, &(t_test_segment){"in.txt", UNQUOTED}}}},
		{4, (t_test_token[]){{WORD, 1, &(t_test_segment){"echo", UNQUOTED}}, {APPEND_OUT_DIR, 1, &(t_test_segment){">>", UNQUOTED}}, {OUT_DIR, 1, &(t_test_segment){">", UNQUOTED}},{WORD, 1, &(t_test_segment){"in.txt", UNQUOTED}}}},
		{4, (t_test_token[]){{WORD, 1, &(t_test_segment){"echo", UNQUOTED}}, {APPEND_OUT_DIR, 1, &(t_test_segment){">>", UNQUOTED}}, {OUT_DIR, 1, &(t_test_segment){">", UNQUOTED}},{WORD, 1, &(t_test_segment){"in.txt", UNQUOTED}}}},
		{1, (t_test_token[]){WORD, 3, (t_test_segment[]){{"hel", UNQUOTED}, {"lo wo", S_QUOTED}, {"rld", UNQUOTED}}}},
		{3, (t_test_token[]){{WORD, 1, (t_test_segment[]){"echo", UNQUOTED}}, {PIPE, 1, (t_test_segment[]){"|", UNQUOTED}}, {WORD, 1, (t_test_segment[]){"hi", UNQUOTED}}}},
		{1, (t_test_token[]){{WORD, 1, &(t_test_segment){"", D_QUOTED}}}},
		{0, NULL},
		{0, NULL},
		{1, (t_test_token[]){{WORD, 1, &(t_test_segment){"", S_QUOTED}}}},
		{1, (t_test_token[]){{WORD, 1, &(t_test_segment){"", S_QUOTED}}}},
		{1, (t_test_token[]){{WORD, 1, &(t_test_segment){"<", D_QUOTED}}}},
		{1, (t_test_token[]){{PIPE, 1, &(t_test_segment){"|", UNQUOTED}}}},
		{1, (t_test_token[]){{HEREDOC, 1, &(t_test_segment){"<<", UNQUOTED}}}},
		{2, (t_test_token[]){{OUT_DIR, 1, &(t_test_segment){">", UNQUOTED}}, {WORD, 1, &(t_test_segment){"file", D_QUOTED}}}},
		{3, (t_test_token[]){{WORD, 1, &(t_test_segment){"echo", D_QUOTED}}, {PIPE, 1, &(t_test_segment){"|", UNQUOTED}}, {WORD, 1, &(t_test_segment){"cat", UNQUOTED}}}},		
		{1, (t_test_token[]){WORD, 2, (t_test_segment[]){{"hello", D_QUOTED}, {"world", S_QUOTED}}}},
		{1, (t_test_token[]){WORD, 2, (t_test_segment[]){{"hello", S_QUOTED}, {"world", D_QUOTED}}}},
		{1, (t_test_token[]){WORD, 2, (t_test_segment[]){{"hello", UNQUOTED}, {"world", S_QUOTED}}}},
		{1, (t_test_token[]){WORD, 2, (t_test_segment[]){{"hello", S_QUOTED}, {"world", UNQUOTED}}}},
		{1, (t_test_token[]){WORD, 1, (t_test_segment[]){"hi\"Bob", S_QUOTED}}},



	};

	while (i < 25)
	{
		actual = lexer_orchestrator(prompt[i], &err);
		helper_test_lexer_orchestrator(prompt[i], actual, test_case[i]);
		free_token_list(actual);
		i++;
	}
}