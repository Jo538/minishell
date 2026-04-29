/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:57:04 by admin             #+#    #+#             */
/*   Updated: 2026/04/29 13:14:53 by admin            ###   ########.fr       */
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
	t_error_exec err = {0};

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

	t_tree node4 = {CMD, (char *[]){"tests/files/unreadable_file.txt", "hello", NULL}, NULL, NULL, NULL};	
	actual = parent_orchestrator(node4, env, &err);
	test_helper(actual, 126, "tests/unreadable_file.txt");

	char *env_with_no_path[] = {"HOME=admin", "VAR=abc", NULL};
	t_tree node5 = {CMD, (char *[]){"echo", "hello", NULL}, NULL, NULL, NULL};	
	actual = parent_orchestrator(node5, env_with_no_path, &err);
	test_helper(actual, 127, "echo hello with missing PATH in env");

	char *no_env[] = {NULL};
	t_tree node6 = {CMD, (char *[]){"echo", "hello", NULL}, NULL, NULL, NULL};	
	actual = parent_orchestrator(node6, no_env, &err);
	test_helper(actual, 127, "echo hello with no env");

	t_tree node7 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){IN_DIR, "tests/files/in.txt", NULL}, NULL, NULL};	
	actual = parent_orchestrator(node7, env, &err);
	test_helper(actual, 0, "echo hello with IN_DIR from in.txt");

	t_tree node8 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/out.txt", NULL}, NULL, NULL};	
	actual = parent_orchestrator(node8, env, &err);
	test_helper(actual, 0, "echo hello with OUT_DIR from out.txt");

	t_tree node9 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/nonexistent_out.txt", NULL}, NULL, NULL};	
	actual = parent_orchestrator(node9, env, &err);
	test_helper(actual, 0, "echo hello with OUT_DIR from nonexistent_out.txt");

	t_tree node10 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){IN_DIR, "tests/files/unreadable_file.txt", NULL}, NULL, NULL};	
	actual = parent_orchestrator(node10, env, &err);
	test_helper(actual, 1, "echo hello with IN_DIR from unreadable_file.txt");

	t_tree node11 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/unwritable_file.txt", NULL}, NULL, NULL};	
	actual = parent_orchestrator(node11, env, &err);
	test_helper(actual, 1, "echo hello with OUT_DIR from unwritable_file.txt");
}
