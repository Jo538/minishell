/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_create_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:03:47 by admin             #+#    #+#             */
/*   Updated: 2026/04/20 12:36:48 by admin            ###   ########.fr       */
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