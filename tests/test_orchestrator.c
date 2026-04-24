/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_orchestrator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 09:43:08 by admin             #+#    #+#             */
/*   Updated: 2026/04/24 22:55:56 by admin            ###   ########.fr       */
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

static void	helper_test_lexer_orchestrator(t_token *actual, t_test_token *expected)
{
	if (actual->type != expected[0].token_type)
		printf("--FAIL--\nactual: %d\nexpected: %d\n", actual->type, expected->token_type);
	if (strcmp(actual->segment->value, expected->segment->value) != 0)
		printf("--FAIL--\nactual: %s\nexpected: %s\n", actual->segment->value, expected->segment->value);
	if (actual->segment->quote_type != expected->segment->quoting_type)
		printf("--FAIL--\nactual: %d\nexpected: %d\n", actual->segment->quote_type, expected->segment->quoting_type);

	actual = actual->next;
	expected = expected + 1;

	if (actual->type != expected->token_type)
		printf("--FAIL--\nactual: %d\nexpected: %d\n", actual->type, expected->token_type);
	if (strcmp(actual->segment->value, expected->segment->value) != 0)
		printf("--FAIL--\nactual: %s\nexpected: %s\n", actual->segment->value, expected->segment->value);
	if (actual->segment->quote_type != expected->segment->quoting_type)
		printf("--FAIL--\nactual: %d\nexpected: %d\n", actual->segment->quote_type, expected->segment->quoting_type);	
}

void	test_lexer_orchestrator(void)
{
	t_error err;
	t_token *actual;
	char *prompt[] = {
		"echo hello"
	};
	t_test_token expected[] = {
		{WORD, 1, &(t_test_segment){"echo", UNQUOTED}},
		{WORD, 1, &(t_test_segment){"hello", UNQUOTED}}
	};
	
	actual = lexer_orchestrator(prompt[0], &err);
	helper_test_lexer_orchestrator(actual, expected);
}