/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:35:33 by admin             #+#    #+#             */
/*   Updated: 2026/04/17 21:06:56 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_find_quoting(void)
{
	t_state	previous_state;
	t_state *previous_state_2;

	ft_bzero(&previous_state, sizeof(t_state));

	previous_state_2 = NULL;
	TEST_ASSERT(find_quoting('a', previous_state_2), UNQUOTED, "-");
	TEST_ASSERT(find_quoting('\'', previous_state_2), S_QUOTED, "-");
	TEST_ASSERT(find_quoting('\"', previous_state_2), D_QUOTED, "-");

	previous_state.quoting = UNQUOTED;
	TEST_ASSERT(find_quoting('a', &previous_state), UNQUOTED, "-");
	TEST_ASSERT(find_quoting('\'', &previous_state), S_QUOTED, "-");
	TEST_ASSERT(find_quoting('\"', &previous_state), D_QUOTED, "-");

	previous_state.quoting = S_QUOTED;
	TEST_ASSERT(find_quoting('a', &previous_state), S_QUOTED, "-");
	TEST_ASSERT(find_quoting('\'', &previous_state), UNQUOTED, "-");
	TEST_ASSERT(find_quoting('\"', &previous_state), S_QUOTED, "-");

	previous_state.quoting = D_QUOTED;
	TEST_ASSERT(find_quoting('a', &previous_state), D_QUOTED, "-");
	TEST_ASSERT(find_quoting('\'', &previous_state), D_QUOTED, "-");
	TEST_ASSERT(find_quoting('\"', &previous_state), UNQUOTED, "-");

}