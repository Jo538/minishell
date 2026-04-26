/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_append_to_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 18:49:13 by admin             #+#    #+#             */
/*   Updated: 2026/04/27 00:48:49 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_add_new_segment(void)
{
	t_error err;
	t_state current_state[] = {
		{'\'', S_QUOTED, ON_WORD, 0},
		{'"', D_QUOTED, ON_WORD, 0},
		{'c', UNQUOTED, ON_WORD, 0},
		{'"', D_QUOTED, ON_WORD, 0},
		{'c', UNQUOTED, ON_WORD, 0}
	};

	t_segment segment[] = {
		{"abc", UNQUOTED, NULL},
		{"abc", UNQUOTED, NULL},
		{"abc", S_QUOTED, NULL},
		{"abc", D_QUOTED, NULL},
		{"abc", UNQUOTED, NULL}
	};

	int i = 0;
	while (i < 5)
	{
		add_new_segment(current_state[i], &segment[i], &err);
		printf("previous segment next: %p\n", segment[i].next);
		printf("current segment value: %s\n", segment[i].next->value);
		printf("current segment quote_type: %d\n", segment[i].next->quote_type);
		printf("current segment next: %p\n\n", segment[i].next->next);
		free(segment[i].next->value);
		free(segment[i].next);
		i++;
	}
}

// void test_append_to_segment(void)
// {
// 	t_error err;
// 	t_state current_state[] = {
// 		{'\'', S_QUOTED, ON_WORD, 0},
// 		{'"', D_QUOTED, ON_WORD, 0},
// 		{'c', UNQUOTED, ON_WORD, 0}
// 	};

// 	t_segment segment[] = {
// 		{"abc", UNQUOTED, NULL},
// 		{"abc", UNQUOTED, NULL},
// 		{"", S_QUOTED, NULL}
// 	};

// 	int i = 0;
// 	while (i < 3)
// 	{
// 		append_to_segment(current_state[i], &segment[i], &err);
// 		printf("segment next: %p\n", segment[i].next);
// 		printf("segment value: %s\n", segment[i].value);
// 		printf("segment quote_type: %d\n", segment[i].quote_type);
// 		free(segment[i].value);
// 		i++;
// 	}
// }

// void test_change_token_type(void)
// {
// 	t_error err;
// 	t_state current_state[] = {
// 		{'<', UNQUOTED, ON_OPERATOR, 2},
// 		{'>', UNQUOTED, ON_OPERATOR, 2}
// 	};

// 	t_token token[] = {
// 		{NULL, IN_DIR, &(t_segment){"<", UNQUOTED, NULL}, NULL},
// 		{NULL, IN_DIR, &(t_segment){">", UNQUOTED, NULL}, NULL}
// 	};

// 	int i = 0;
// 	while (i < 2)
// 	{
// 		change_token_type(current_state[i], &token[i], &err);
// 		printf("token type: %d\n", token[i].type);
// 		printf("segment value: %s\n", token[i].segment->value);
// 		free(token[i].segment->value);
// 		i++;		
// 	}
// }