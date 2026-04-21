/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_create_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:03:47 by admin             #+#    #+#             */
/*   Updated: 2026/04/21 20:38:00 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_find_token_type(void)
{
	t_state	array[] = {
		{'|', UNQUOTED, ON_OPERATOR, 0},
		{'<', UNQUOTED, ON_OPERATOR, 0},
		{'>', UNQUOTED, ON_OPERATOR, 0},
		{'<', UNQUOTED, ON_OPERATOR, 2},
		{'>', UNQUOTED, ON_OPERATOR, 2},
		{'c', UNQUOTED, ON_WORD, 0},
		{'c', S_QUOTED, ON_WORD, 0},
		{'|', S_QUOTED, ON_WORD, 0},
		{'<', S_QUOTED, ON_WORD, 0},
		{'c', D_QUOTED, ON_WORD, 0},
		{'|', D_QUOTED, ON_WORD, 0},
		{'<', D_QUOTED, ON_WORD, 0},
		{'<', UNQUOTED, ON_OPERATOR, 3}
	};
	
	TEST_ASSERT(find_token_type(array[0]), PIPE, "-");
	TEST_ASSERT(find_token_type(array[1]), IN_DIR, "-");
	TEST_ASSERT(find_token_type(array[2]), OUT_DIR, "-");
	TEST_ASSERT(find_token_type(array[3]), HEREDOC, "-");
	TEST_ASSERT(find_token_type(array[4]), APPEND_OUT_DIR, "-");
	TEST_ASSERT(find_token_type(array[5]), WORD, "-");
	TEST_ASSERT(find_token_type(array[6]), WORD, "-");
	TEST_ASSERT(find_token_type(array[7]), WORD, "-");
	TEST_ASSERT(find_token_type(array[8]), WORD, "-");
	TEST_ASSERT(find_token_type(array[9]), WORD, "-");
	TEST_ASSERT(find_token_type(array[10]), WORD, "-");
	TEST_ASSERT(find_token_type(array[11]), WORD, "-");
	TEST_ASSERT(find_token_type(array[12]), IN_DIR, "-");

	// Unquoted |
	// Unquoted <
	// Unquoted >
	// Unquoted <<
	// Unquoted >>
	// Unquoted char c
	// Single quoted char c
	// Single quoted |
	// Single quoted <<
	// Double quoted char c
	// Double quoted |
	// Double quoted <<
}

void	test_check_new_token(void)
{

		t_state previous_array[] = {
		{'b', UNQUOTED, ON_WORD, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'|', UNQUOTED, ON_OPERATOR, 0},
		{'|', UNQUOTED, ON_OPERATOR, 0},
		{'c', UNQUOTED, ON_WORD, 0},
		{'c', UNQUOTED, ON_WORD, 0},
		{'b', S_QUOTED, ON_WORD, 0},
		{'|', D_QUOTED, ON_WORD, 0},
		{'<', UNQUOTED, ON_OPERATOR, 1},
		{'<', UNQUOTED, ON_OPERATOR, 2},
	};

	t_state current_array[] = {
		{'c', UNQUOTED, ON_WORD, 0},
		{'<', UNQUOTED, ON_OPERATOR, 0},
		{'c', UNQUOTED, ON_WORD, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'c', UNQUOTED, ON_WORD, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'<', UNQUOTED, ON_OPERATOR, 0},
		{'c', S_QUOTED, ON_WORD, 0},
		{'<', D_QUOTED, ON_WORD, 0},
		{'<', UNQUOTED, ON_OPERATOR, 2},
		{'<', UNQUOTED, ON_OPERATOR, 3},
	};

	TEST_ASSERT(check_new_token(previous_array[0], current_array[0]), 0, "-");
	TEST_ASSERT(check_new_token(previous_array[1], current_array[1]), 1, "-");
	TEST_ASSERT(check_new_token(previous_array[2], current_array[2]), 1, "-");
	TEST_ASSERT(check_new_token(previous_array[3], current_array[3]), 0, "-");
	TEST_ASSERT(check_new_token(previous_array[4], current_array[4]), 1, "-");
	TEST_ASSERT(check_new_token(previous_array[5], current_array[5]), 0, "-");
	TEST_ASSERT(check_new_token(previous_array[6], current_array[6]), 1, "-");
	TEST_ASSERT(check_new_token(previous_array[7], current_array[7]), 0, "-");
	TEST_ASSERT(check_new_token(previous_array[8], current_array[8]), 0, "-");
	TEST_ASSERT(check_new_token(previous_array[9], current_array[9]), 2, "-");
	TEST_ASSERT(check_new_token(previous_array[10], current_array[10]), 1, "-");
}


void	test_create_token(void)
{
	t_error err = 0;
	t_state array[] = {
		{'e', UNQUOTED, ON_WORD, 0},
		{'e', UNQUOTED, ON_WORD, 0},
		{'\'', S_QUOTED, ON_WORD, 0},
		{'"', D_QUOTED, ON_WORD, 0},
		{'e', UNQUOTED, ON_WORD, 0}
	};
	
	t_token previous_token = {NULL, PIPE, NULL, NULL};
	
	t_token *new_token = create_token(array[0], NULL, &err);
	printf("before: %p\n", new_token->before);
	printf("next: %p\n", new_token->next);
	printf("token type: %d\n", new_token->type);
	printf("segment value: %s\n", new_token->segment->value);
	printf("segment quoting type: %d\n", new_token->segment->quote_type);
	printf("segment next: %p\n", new_token->segment->next);
	free(new_token->segment->value);
	free(new_token->segment);
	free(new_token);
	
	int i = 1;
	while (i < 5)
	{
		new_token = create_token(array[i], &previous_token, &err);
		printf("before: %p\n", new_token->before);
		printf("next: %p\n", new_token->next);
		printf("token type: %d\n", new_token->type);
		printf("segment value: %s\n", new_token->segment->value);
		printf("segment quoting type: %d\n", new_token->segment->quote_type);
		printf("segment next: %p\n", new_token->segment->next);
		free(new_token->segment->value);
		free(new_token->segment);
		free(new_token);
		i++;
	}
	// Check first token gets created
	// Check second token gets created
	// Check Unquoted segment gets created
	// Check S_quoted segment gets created
	// Check D_quoted segment gets created (no " but the letter from after)
	// Check malloc error
	// Check 
}