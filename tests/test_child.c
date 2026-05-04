/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:57:04 by admin             #+#    #+#             */
/*   Updated: 2026/05/04 21:57:33 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

#define CMD 1
#define PIPE 2

static int helper_exit_code(int actual, int expected)
{
	if (actual != expected)
	{
		printf("--FAIL--\nactual: %d\nexpected: %d\n",actual, expected);
		return (1);
	}
	return (0);
}

static int helper_output(char *actual, char *expected)
{
	int len = ft_strlen(expected);
	if (strncmp(actual, expected, len))
	{
		printf("--FAIL--\nactual: %s\nexpected: %s\n", actual, expected);
		return (1);		
	}
	return (0);
}

static void helper_orchestrator(int test_num, char *cmd, char *actual_output, char *expected_output, int actual_exit_code, int expected_exit_code)
{
	printf("TEST %d: %s\n", test_num, cmd);
	if (!helper_exit_code(actual_exit_code, expected_exit_code)
		&& !helper_output(actual_output, expected_output))
		printf("%s\n", "--SUCCESS--");	
}

void test_improved_version_executor(void)
{
	char *env[] = {"HOME=admin", "PATH=/local/sbin:/local/bin:/bin", NULL};
	t_error_exec err = {0};
	int copy_fd1;
	int fd;
	int actual;
	char buffer[4096] = {0};

	//create temp folder and test_outputs folder
	system("mkdir -p tests/temp/test_outputs");

	// Stores log files before test was run
	glob_t logs_before;
	glob("vg*.log", 0, NULL, &logs_before);

	// Test 1: echo hello
	fd = open("tests/temp/test_outputs/test_1.txt", O_CREAT | O_RDWR, 0644);
	t_tree node = {CMD, (char *[]){"echo", "hello", NULL}, NULL, NULL, NULL};
	copy_fd1 = dup(1);
	dup2(fd, 1);
	fcntl(copy_fd1, F_SETFD, FD_CLOEXEC);
	close(fd);
	actual = execute(&node, env);
	dup2(copy_fd1, 1);
	close(copy_fd1);
	fd = open("tests/temp/test_outputs/test_1.txt", O_RDWR, 0644);
	read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	helper_orchestrator(1, "echo hello", buffer, "hello", actual, 0);

	// Stores log files after test was run
	glob_t logs_after;
	int count_before = 0;
	int count_after = 0;
	int len;
	glob("vg*.log", 0, NULL, &logs_after);
	while (logs_before.gl_pathv && logs_before.gl_pathv[count_before])
		count_before++;
	while (logs_after.gl_pathv[count_after])
		count_after++;
	len = count_after - count_before;
	
	char *array[len + 1];
	int i = 0;
	while (i < len)
	{
		array[i] = logs_after.gl_pathv[count_before + i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		printf("%d: %s\n", i, array[i]);
		i++;
	}
	globfree(&logs_before);
	globfree(&logs_after);	
}

// void	test_parent_orchestrator(void)
// {
// 	t_tree *node = &(t_tree){CMD, (char *[]){"echo", "hello", NULL}, NULL, NULL, NULL};
// 	char *env[] = {"HOME=admin", "PATH=/local/sbin:/local/bin:/bin", NULL};
// 	t_error_exec err = {0};

// 	int actual = cmd_orchestrator(node, env, &err);
// 	test_helper(actual, 0, "echo hello");

// 	t_tree node1 = {CMD, (char *[]){"/bin/echo", "hello", NULL}, NULL, NULL, NULL};	
// 	actual = cmd_orchestrator(&node1, env, &err);
// 	test_helper(actual, 0, "/bin/echo hello");

// 	t_tree node2 = {CMD, (char *[]){"echoo", "hello", NULL}, NULL, NULL, NULL};	
// 	actual = cmd_orchestrator(&node2, env, &err);
// 	test_helper(actual, 127, "echoo hello");

// 	t_tree node3 = {CMD, (char *[]){"/bin/echoo", "hello", NULL}, NULL, NULL, NULL};	
// 	actual = cmd_orchestrator(&node3, env, &err);
// 	test_helper(actual, 127, "/bin/echoo hello");

// 	t_tree node4 = {CMD, (char *[]){"tests/files/unreadable_file.txt", "hello", NULL}, NULL, NULL, NULL};	
// 	actual = cmd_orchestrator(&node4, env, &err);
// 	test_helper(actual, 126, "tests/unreadable_file.txt");

// 	char *env_with_no_path[] = {"HOME=admin", "VAR=abc", NULL};
// 	t_tree node5 = {CMD, (char *[]){"echo", "hello", NULL}, NULL, NULL, NULL};	
// 	actual = cmd_orchestrator(&node5, env_with_no_path, &err);
// 	test_helper(actual, 127, "echo hello with missing PATH in env");

// 	char *no_env[] = {NULL};
// 	t_tree node6 = {CMD, (char *[]){"echo", "hello", NULL}, NULL, NULL, NULL};	
// 	actual = cmd_orchestrator(&node6, no_env, &err);
// 	test_helper(actual, 127, "echo hello with no env");

// 	t_tree node7 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){IN_DIR, "tests/files/in.txt", NULL}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node7, env, &err);
// 	test_helper(actual, 0, "echo hello with IN_DIR from in.txt");

// 	t_tree node8 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/out.txt", NULL}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node8, env, &err);
// 	test_helper(actual, 0, "echo hello with OUT_DIR from out.txt");

// 	t_tree node9 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/nonexistent_out.txt", NULL}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node9, env, &err);
// 	test_helper(actual, 0, "echo hello with OUT_DIR from nonexistent_out.txt");

// 	t_tree node10 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){IN_DIR, "tests/files/unreadable_file.txt", NULL}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node10, env, &err);
// 	test_helper(actual, 1, "echo hello with IN_DIR from unreadable_file.txt");

// 	t_tree node11 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/unwritable_file.txt", NULL}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node11, env, &err);
// 	test_helper(actual, 1, "echo hello with OUT_DIR from unwritable_file.txt");

// 	t_tree node12 = {CMD, (char *[]){"cat", "Makefile", NULL}, &(t_redir){OUT_DIR, "tests/files/out.txt", &(t_redir){OUT_DIR, "tests/files/out1.txt", NULL}}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node12, env, &err);
// 	test_helper(actual, 0, "cat Makefile with 2 OUT_DIR to out1.txt");
// 	unlink("tests/files/out1.txt");
	
// 	t_tree node13 = {CMD, (char *[]){"cat", "Makefile", NULL}, &(t_redir){OUT_DIR, "tests/files/out1.txt", &(t_redir){OUT_DIR, "tests/files/out2.txt", NULL}}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node13, env, &err);
// 	test_helper(actual, 0, "cat Makefile with 2 OUT_DIR to out2.txt, out1.txt doesn't exist");

// 	t_tree node14 = {CMD, (char *[]){"cat", "Makefile", NULL}, &(t_redir){OUT_DIR, "tests/files/unwritable_file.txt", &(t_redir){OUT_DIR, "tests/files/out3.txt", NULL}}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node14, env, &err);
// 	test_helper(actual, 1, "cat Makefile with 2 OUT_DIR to out3.txt, with transition through unwritable_file.txt");

// 	t_tree node15 = {CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "tests/files/empty.txt", &(t_redir){IN_DIR, "Makefile", &(t_redir){OUT_DIR, "tests/files/out4.txt", NULL}}}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node15, env, &err);
// 	test_helper(actual, 0, "cat Makefile with 2 IN_DIR to out4.txt");

// 	t_tree node16 = {CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "tests/files/empty.txt", &(t_redir){OUT_DIR, "tests/files/out5.txt", &(t_redir){IN_DIR, "Makefile", NULL}}}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node16, env, &err);
// 	test_helper(actual, 0, "cat Makefile with 1 IN_DIR, then 1 OUT_DIR, then 1 IN_DIR, out5.txt created");

// 	t_tree node17 = {CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "tests/files/tirade_2.txt", &(t_redir){APPEND_OUT_DIR, "tests/files/tirade_1.txt", NULL}}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node17, env, &err);
// 	test_helper(actual, 0, "cat tirade_2.txt with APPEND_OUT_DIR to tirade_1.txt");

// 	t_tree node18 = {CMD, (char *[]){"cat", NULL}, &(t_redir){HEREDOC, "hello jo\n", NULL}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node18, env, &err);
// 	test_helper(actual, 0, "cat \"hello jo\" with HEREDOC");

// 	t_tree node19 = {CMD, (char *[]){"cat", NULL}, &(t_redir){HEREDOC, "test 1\ntest 2\n", &(t_redir){OUT_DIR, "tests/files/out.txt", NULL}}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node19, env, &err);
// 	test_helper(actual, 0, "cat test 1 test 2 with HEREDOC and OUT_DIR to out.txt");

// 	t_tree node20 = {CMD, (char *[]){"cat", "Makefile", NULL}, &(t_redir){OUT_DIR, "", NULL}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node20, env, &err);
// 	test_helper(actual, 1, "cat Makefile with OUT_DIR to \"\"");

// 	t_tree node21 = {CMD, (char *[]){"cat", "", NULL}, NULL, NULL, NULL};	
// 	actual = cmd_orchestrator(&node21, env, &err);
// 	test_helper(actual, 1, "cat \"\"");

// 	t_tree node22 = {CMD, (char *[]){"cat", NULL}, &(t_redir){APPEND_OUT_DIR, "", NULL}, NULL, NULL};	
// 	actual = cmd_orchestrator(&node22, env, &err);
// 	test_helper(actual, 1, "cat >> \"\"");

// 	unlink("tests/files/out1.txt");
// 	unlink("tests/files/out2.txt");
// 	unlink("tests/files/out4.txt");
// 	unlink("tests/files/out5.txt");	
// }

// void test_pipe_orchestrator(void)
// {
// 	char *env[] = {"HOME=admin", "PATH=/local/sbin:/local/bin:/bin:/usr/bin", NULL};
// 	t_error_exec err = {0};
// 	t_tree node0 = {CMD, (char *[]){"cat", "Makefile", NULL}, NULL, NULL, NULL};
// 	t_tree node1 = {CMD, (char *[]){"wc", "-l", NULL}, NULL, NULL, NULL};
// 	t_tree pipe_node = {PIPE, NULL, NULL, &node0, &node1};

// 	int actual = pipe_orchestrator(&pipe_node, env, &err);
// 	test_helper(actual, 0, "cat Makefile | wc -l");

// 	t_tree node2 = {CMD, (char *[]){"/bin/cat", "Makefile", NULL}, NULL, NULL, NULL};
// 	t_tree node3 = {CMD, (char *[]){"wc", "-l", NULL}, NULL, NULL, NULL};
// 	t_tree pipe_node1 = {PIPE, NULL, NULL, &node2, &node3};
// 	actual = pipe_orchestrator(&pipe_node1, env, &err);
// 	test_helper(actual, 0, "/bin/cat Makefile | wc -l");

// 	t_tree node4 = {CMD, (char *[]){"catt", "Makefile", NULL}, NULL, NULL, NULL};
// 	t_tree node5 = {CMD, (char *[]){"wc", "-l", NULL}, NULL, NULL, NULL};
// 	t_tree pipe_node2 = {PIPE, NULL, NULL, &node4, &node5};
// 	actual = pipe_orchestrator(&pipe_node2, env, &err);
// 	test_helper(actual, 0, "catt Makefile | wc -l");

// 	t_tree node6 = {CMD, (char *[]){"cat", "Makefile", NULL}, NULL, NULL, NULL};
// 	t_tree node7 = {CMD, (char *[]){"wcc", "-l", NULL}, NULL, NULL, NULL};
// 	t_tree pipe_node3 = {PIPE, NULL, NULL, &node6, &node7};
// 	actual = pipe_orchestrator(&pipe_node3, env, &err);
// 	test_helper(actual, 127, "cat Makefile | wcc -l");

// 	t_tree node8 = {CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "Makefile", NULL}, NULL, NULL};
// 	t_tree node9 = {CMD, (char *[]){"wc", "-l", NULL}, NULL, NULL, NULL};
// 	t_tree pipe_node4 = {PIPE, NULL, NULL, &node8, &node9};
// 	actual = pipe_orchestrator(&pipe_node4, env, &err);
// 	test_helper(actual, 0, "cat < Makefile | wc -l");

// 	char *env_with_no_path[] = {"HOME=admin", "VAR=abc", NULL};
// 	t_tree node10 = {CMD, (char *[]){"cat", "Makefile", NULL}, NULL, NULL, NULL};
// 	t_tree node11 = {CMD, (char *[]){"wc", "-l", NULL}, NULL, NULL, NULL};
// 	t_tree pipe_node5 = {PIPE, NULL, NULL, &node10, &node11};
// 	actual = pipe_orchestrator(&pipe_node5, env_with_no_path, &err);
// 	test_helper(actual, 127, "cat Makefile | wc -l with no PATH var in environment");
// }

// void test_orchestrator(void)
// {
// 	char *env[] = {"HOME=admin", "PATH=/local/sbin:/local/bin:/bin:/usr/bin", NULL};
// 	t_error_exec err = {0};

// 	t_tree inner_pipe_left_node = {CMD, (char *[]){"cat", "Makefile", NULL}, NULL, NULL, NULL};
// 	t_tree inner_pipe_right_node = {CMD, (char *[]){"cat", NULL}, NULL, NULL, NULL};
// 	t_tree inner_pipe = {PIPE, NULL, NULL, &inner_pipe_left_node, &inner_pipe_right_node};
	
// 	t_tree outer_pipe_right_node = {CMD, (char *[]){"cat", NULL}, NULL, NULL, NULL};
// 	t_tree outer_pipe = {PIPE, NULL, NULL, &inner_pipe, &outer_pipe_right_node};

// 	int actual = execute(&outer_pipe, env);
// 	test_helper(actual, 0, "cat Makefile | cat | cat");	
// }
