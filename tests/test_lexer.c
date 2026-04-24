/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:35:33 by admin             #+#    #+#             */
/*   Updated: 2026/04/24 10:05:15 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static int	helper_create_current_state_2(t_state result, t_state expected)
{
	if (result.c != expected.c)
		return (FAIL);
	if (result.quoting != expected.quoting)
		return (FAIL);
	if (result.char_type != expected.char_type)
		return (FAIL);
	if (result.repeat != expected.repeat)
		return (FAIL);
	return (PASS);	
}

static void	helper_create_current_state_1(char *cmd, t_state array[])
{
	t_error	err;
	int len = strlen(cmd);
	int i = 0;
	t_state	current_state;
	int		pass_or_fail;

	while (i < len)
	{
		current_state = create_current_state(cmd[i], i, array[i]);
		pass_or_fail = helper_create_current_state_2(current_state, array[i + 1]);
		if (pass_or_fail == PASS)
			printf("[%d] %c: %s\n", i, cmd[i], "SUCCESS");
		else
		{
			printf("[%d] %c: %s\n", i, cmd[i],  "FAILURE");		
			printf("Actual --> %c (char), %d (quoting), %d (char_type), %d (repeat)\n", current_state.c,current_state.quoting, current_state.char_type, current_state.repeat);	
			printf("Expected --> %c (char), %d (quoting), %d (char_type), %d (repeat)\n", array[i + 1].c, array[i + 1].quoting, array[i + 1].char_type, array[i + 1].repeat);
		}
		i++;
	}
}

void	test_create_current_state(void)
{
	// Test echo "hello"world>>> out.txt //

	char *cmd = "echo \"hello\"world>>> out.txt";
	t_state array[] = {
		{},
		{'e', UNQUOTED, ON_WORD, 0},
		{'c', UNQUOTED, ON_WORD, 0},
		{'h', UNQUOTED, ON_WORD, 0},
		{'o', UNQUOTED, ON_WORD, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'"', D_QUOTED, ON_WORD, 0},
		{'h', D_QUOTED, ON_WORD, 0},
		{'e', D_QUOTED, ON_WORD, 0},
		{'l', D_QUOTED, ON_WORD, 0},
		{'l', D_QUOTED, ON_WORD, 0},
		{'o', D_QUOTED, ON_WORD, 0},
		{'"', UNQUOTED, ON_WORD, 0},
		{'w', UNQUOTED, ON_WORD, 0},
		{'o', UNQUOTED, ON_WORD, 0},
		{'r', UNQUOTED, ON_WORD, 0},
		{'l', UNQUOTED, ON_WORD, 0},
		{'d', UNQUOTED, ON_WORD, 0},
		{'>', UNQUOTED, ON_OPERATOR, 1},
		{'>', UNQUOTED, ON_OPERATOR, 2},
		{'>', UNQUOTED, ON_OPERATOR, 3},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'o', UNQUOTED, ON_WORD, 0},
		{'u', UNQUOTED, ON_WORD, 0},
		{'t', UNQUOTED, ON_WORD, 0},
		{'.', UNQUOTED, ON_WORD, 0},
		{'t', UNQUOTED, ON_WORD, 0},
		{'x', UNQUOTED, ON_WORD, 0},
		{'t', UNQUOTED, ON_WORD, 0}	
	};
	
	helper_create_current_state_1(cmd, array);
	
	cmd = " echo \"j'arrive\" | cat";

	t_state array_1[] = {
		{},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'e', UNQUOTED, ON_WORD, 0},
		{'c', UNQUOTED, ON_WORD, 0},
		{'h', UNQUOTED, ON_WORD, 0},
		{'o', UNQUOTED, ON_WORD, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'"', D_QUOTED, ON_WORD, 0},
		{'j', D_QUOTED, ON_WORD, 0},
		{'\'', D_QUOTED, ON_WORD, 0},
		{'a', D_QUOTED, ON_WORD, 0},
		{'r', D_QUOTED, ON_WORD, 0},
		{'r', D_QUOTED, ON_WORD, 0},
		{'i', D_QUOTED, ON_WORD, 0},
		{'v', D_QUOTED, ON_WORD, 0},
		{'e', D_QUOTED, ON_WORD, 0},
		{'"', UNQUOTED, ON_WORD, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'|', UNQUOTED, ON_OPERATOR, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'c', UNQUOTED, ON_WORD, 0},
		{'a', UNQUOTED, ON_WORD, 0},
		{'t', UNQUOTED, ON_WORD, 0}
	};

	helper_create_current_state_1(cmd, array_1);
	
	cmd = "cat << STOP | ls 'abc'";

	t_state array_2[] = {
		{},
		{'c', UNQUOTED, ON_WORD, 0},
		{'a', UNQUOTED, ON_WORD, 0},
		{'t', UNQUOTED, ON_WORD, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'<', UNQUOTED, ON_OPERATOR, 1},
		{'<', UNQUOTED, ON_OPERATOR, 2},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'S', UNQUOTED, ON_WORD, 0},
		{'T', UNQUOTED, ON_WORD, 0},
		{'O', UNQUOTED, ON_WORD, 0},
		{'P', UNQUOTED, ON_WORD, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'|', UNQUOTED, ON_OPERATOR, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'l', UNQUOTED, ON_WORD, 0},
		{'s', UNQUOTED, ON_WORD, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'\'', S_QUOTED, ON_WORD, 0},
		{'a', S_QUOTED, ON_WORD, 0},
		{'b', S_QUOTED, ON_WORD, 0},
		{'c', S_QUOTED, ON_WORD, 0},
		{'\'', UNQUOTED, ON_WORD, 0}
	};

	helper_create_current_state_1(cmd, array_2);

	cmd = "hel'lo th\"e>e' > out";

	t_state array_3[] = {
		{},
		{'h', UNQUOTED, ON_WORD, 0},
		{'e', UNQUOTED, ON_WORD, 0},
		{'l', UNQUOTED, ON_WORD, 0},
		{'\'', S_QUOTED, ON_WORD, 0},
		{'l', S_QUOTED, ON_WORD, 0},
		{'o', S_QUOTED, ON_WORD, 0},
		{' ', S_QUOTED, ON_WORD, 0},
		{'t', S_QUOTED, ON_WORD, 0},
		{'h', S_QUOTED, ON_WORD, 0},
		{'\"', S_QUOTED, ON_WORD, 0},
		{'e', S_QUOTED, ON_WORD, 0},
		{'>', S_QUOTED, ON_WORD, 0},
		{'e', S_QUOTED, ON_WORD, 0},
		{'\'', UNQUOTED, ON_WORD, 0},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'>', UNQUOTED, ON_OPERATOR, 1},
		{' ', UNQUOTED, ON_SPACE, 0},
		{'o', UNQUOTED, ON_WORD, 0},
		{'u', UNQUOTED, ON_WORD, 0},
		{'t', UNQUOTED, ON_WORD, 0}
	};

	helper_create_current_state_1(cmd, array_3);

}
	