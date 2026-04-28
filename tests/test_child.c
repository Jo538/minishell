/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:57:04 by admin             #+#    #+#             */
/*   Updated: 2026/04/28 20:03:31 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

#define CMD 0
#define PIPE 1

static void test_helper(int actual, int expected, char *cmd)
{
	if (actual != expected)
		printf("--FAIL-- %s\nactual: %d\nexpected: %d\n", cmd, actual, expected);
	else
		printf("--SUCCESS-- %s\n", cmd);
}

void	test_parent_orchestrator(void)
{
	t_tree node = {CMD, (char *[]){"echo", "hello", NULL}, NULL, NULL, NULL};
	char *env[] = {"HOME=admin", "PATH=/local/sbin:/local/bin:/bin", NULL};
	t_error err = 0;

	int actual = parent_orchestrator(node, env, &err);
	test_helper(actual, 0, "echo hello");

	t_tree node1 = {CMD, (char *[]){"/bin/echo", "hello", NULL}, NULL, NULL, NULL};	
	actual = parent_orchestrator(node1, env, &err);
	test_helper(actual, 0, "/bin/echo hello");

	t_tree node2 = {CMD, (char *[]){"echoo", "hello", NULL}, NULL, NULL, NULL};	
	actual = parent_orchestrator(node2, env, &err);
	test_helper(actual, 127, "echoo hello");

	t_tree node3 = {CMD, (char *[]){"/bin/echoo", "hello", NULL}, NULL, NULL, NULL};	
	actual = parent_orchestrator(node3, env, &err);
	test_helper(actual, 127, "/bin/echoo hello");
}
