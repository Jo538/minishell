/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:57:04 by admin             #+#    #+#             */
/*   Updated: 2026/05/06 00:06:58 by admin            ###   ########.fr       */
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

static int valgrind_checks(char *array_of_files[], int expected_fds)
{
	int flag_no_fd_issue = 0;
	int flag_no_leak = 0;
	int flag_no_error = 0;

	FILE *fp;
	char *line = NULL;
	size_t cap = 0;
	char path[64];

	int i = 0;
	while (array_of_files[i])
	{
		fp = fopen(array_of_files[i], "r");
		snprintf(path, sizeof(path), "FILE DESCRIPTORS: %d open", expected_fds);
		while (getline(&line, &cap, fp) != -1)
		{
			if (strstr(line, path))
				flag_no_fd_issue = 1;
			if (strstr(line, "definitely lost: 0 bytes in 0 blocks"))
				flag_no_leak = 1;
			if (strstr(line, "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"))
				flag_no_error = 1;			
		}
		free(line);
		fclose(fp);
		if (!flag_no_fd_issue || !flag_no_leak || !flag_no_error)
		{
			printf("%s\n", "--FAIL-- Valgrind error");
			return (1);	
		}
		i++;
	}
	return (0);
}

static char **make_logs_array(glob_t *logs_before)
{
	glob_t logs_after;
	int count_before = 0;
	int count_after = 0;
	int len;

	glob("vg*.log", 0, NULL, &logs_after);
	while (logs_before->gl_pathv && logs_before->gl_pathv[count_before])
		count_before++;
	while (logs_after.gl_pathv[count_after])
		count_after++;
	len = count_after - count_before;
	
	char **array = ft_calloc(len + 1, sizeof(char *));
	int i = 0;
	while (i < len)
	{
		array[i] = ft_strdup(logs_after.gl_pathv[count_before + i]);
		i++;
	}
	globfree(logs_before);
	globfree(&logs_after);	
	return (array);
}

static int create_output_file(int test_num, char *cmd, char *output_file, int error)
{
	int copy_fd = -1;
	int fd;
	char path[64];                                                                                                                                                                                                                                                                     

	if (output_file)
		return (copy_fd);

  	snprintf(path, sizeof(path), "tests/temp/test_outputs/test_%d.txt", test_num);
	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (error)
	{
		copy_fd = dup(2);
		dup2(fd, 2);		
	}
	else
	{
		copy_fd = dup(1);
		dup2(fd, 1);
	}
	fcntl(copy_fd, F_SETFD, FD_CLOEXEC);
	close(fd);
	return (copy_fd);
}

static char *read_output_file(int test_num, int copy_fd, char *cmd, char *output_file, int error)
{
	int fd;
	char path[64];
	char buffer[4096] = {0};
	char *result;

	if (!output_file)
	{
		snprintf(path, sizeof(path), "tests/temp/test_outputs/test_%d.txt", test_num);
		if (error)
			dup2(copy_fd, 2);
		else
			dup2(copy_fd, 1);
		close(copy_fd);
	}
	if (!output_file)
		fd = open(path, O_RDONLY);
	else
		fd = open(output_file, O_RDONLY);
	read(fd, buffer, sizeof(buffer) - 1);
	result = ft_strdup(buffer);
	close(fd);
	return (result);
}

static void run_checks(int test_num, char *cmd, int actual_exit_code, int expected_exit_code, char *result, char *expected_output, char **array_of_files, int expected_fds)
{
	printf("TEST %d: %s\n", test_num, cmd);
	if (!helper_exit_code(actual_exit_code, expected_exit_code)
		&& !helper_output(result, expected_output))
		printf("%s\n", "--SUCCESS--");
	fflush(stdout);
	fflush(stderr);		
}

static void clean_heap(char **array_of_files, char *result)
{
	int i = 0;
	while (array_of_files[i])
	{
		free(array_of_files[i]);
		i++;
	}
	free(array_of_files);
	i = 0;
	free(result);	
}

static void helper_orchestrator(int test_num, char *cmd, char **env, t_tree *node, char *expected_output, int expected_exit_code, char *output_file, int error, int expected_fds)
{
	int actual_exit_code;
	char *result = NULL;

	glob_t logs_before = {0};
	
    
	int copy_fd = create_output_file(test_num, cmd, output_file, error);
	glob("vg*.log", 0, NULL, &logs_before);
	actual_exit_code = execute(node, env);
	char **array_of_files = make_logs_array(&logs_before);
	result = read_output_file(test_num, copy_fd, cmd, output_file, error);
	run_checks(test_num, cmd, actual_exit_code, expected_exit_code, result, expected_output, array_of_files, expected_fds);
	clean_heap(array_of_files, result);
}

void test_improved_version_executor(void)
{
	char *env[] = {"HOME=admin", "PATH=/local/sbin:/local/bin:/bin", NULL};
	t_error_exec err = {0};
	int copy_fd1;
	int fd;
	int actual;
	char buffer[4096] = {0};
	glob_t logs_before;

	//create temp folder and test_outputs folder
	system("mkdir -p tests/temp/test_outputs");


	// Test 1: echo hello
	t_tree node1 = {CMD, (char *[]){"echo", "hello", NULL}, NULL, NULL, NULL};
	helper_orchestrator(1, "echo hello", env, &node1, "hello", 0, NULL, 0, 3);

	// Test 2: /bin/echo hello
	t_tree node2 = {CMD, (char *[]){"/bin/echo", "hello", NULL}, NULL, NULL, NULL};	
	helper_orchestrator(2, "/bin/echo hello", env, &node2, "hello", 0, NULL, 0, 3);

	// Test 3: echoo hello
	t_tree node3 = {CMD, (char *[]){"echoo", "hello", NULL}, NULL, NULL, NULL};	
	helper_orchestrator(3, "echoo hello", env, &node3, "echoo: Command not found", 127, NULL, 1, 4);

	// Test 4: /bin/echoo hello
	t_tree node4 = {CMD, (char *[]){"/bin/echoo", "hello", NULL}, NULL, NULL, NULL};
	helper_orchestrator(4, "echoo hello", env, &node4, "/bin/echoo: No such file or directory", 127, NULL, 1, 4);

	// Test 5: tests/files/unreadable_file.txt hello
	t_tree node5 = {CMD, (char *[]){"tests/files/unreadable_file.txt", "hello", NULL}, NULL, NULL, NULL};
	helper_orchestrator(5, "tests/files/unreadable_file.txt hello", env, &node5, "tests/files/unreadable_file.txt: Permission denied", 126, NULL, 1, 4);

	// Test 6 cat < tests/files/in.txt
	t_tree node6 = {CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "tests/files/in.txt", NULL}, NULL, NULL};
	helper_orchestrator(6, "cat < tests/files/in.txt", env, &node6, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, NULL, 0, 3);

	// Test 7: echo hello > tests/files/out.txt
	t_tree node7 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/out.txt", NULL}, NULL, NULL};
	helper_orchestrator(7, "echo hello > tests/files/out.txt", env, &node7, "hello", 0, "tests/files/out.txt", 0, 3);

	// Test 8: echo hello > tests/files/nonexistent_out.txt
	t_tree node8 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/nonexistent_out.txt", NULL}, NULL, NULL};
	helper_orchestrator(8, "echo hello > tests/files/nonexistent_out.txt", env, &node8, "hello", 0, "tests/files/nonexistent_out.txt", 0, 3);

	// Test 9: cat < tests/files/unreadable_file.txt
	t_tree node9 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){IN_DIR, "tests/files/unreadable_file.txt", NULL}, NULL, NULL};
	helper_orchestrator(9, "cat < tests/files/unreadable_file.txt", env, &node9, "tests/files/unreadable_file.txt: Permission denied", 1, NULL, 1, 3);

	// Test 10: echo hello > tests/files/unwritable_file.txt
	t_tree node10 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/unwritable_file.txt", NULL}, NULL, NULL};
	helper_orchestrator(10, "echo hello > tests/files/unwritable_file.txt", env, &node10, "tests/files/unwritable_file.txt: Permission denied", 1, NULL, 1, 3);

	// Test 11: echo Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap ! > tests/files/out.txt > tests/files/out1.txt
	t_tree node11 = {CMD, (char *[]){"echo", "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", NULL}, &(t_redir){OUT_DIR, "tests/files/out.txt", &(t_redir){OUT_DIR, "tests/files/out1.txt", NULL}}, NULL, NULL};
	helper_orchestrator(11, "echo Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap ! > tests/files/out.txt > tests/files/out1.txt", env, &node11, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, "tests/files/out1.txt", 1, 3);

	// Test 12: echo Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap ! > tests/files/out2.txt > tests/files/out3.txt
	t_tree node12 = {CMD, (char *[]){"echo", "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", NULL}, &(t_redir){OUT_DIR, "tests/files/out2.txt", &(t_redir){OUT_DIR, "tests/files/out3.txt", NULL}}, NULL, NULL};
	helper_orchestrator(12, "echo Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap ! > tests/files/out2.txt > tests/files/out3.txt", env, &node12, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, "tests/files/out3.txt", 1, 3);

	// Test 13: echo hello > tests/files/unwritable_file.txt > tests/files/out4.txt
	t_tree node13 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/unwritable_file.txt", &(t_redir){OUT_DIR, "tests/files/out4.txt", NULL}}, NULL, NULL};
	helper_orchestrator(13, "echo hello > tests/files/unwritable_file.txt > tests/files/out4.txt", env, &node13, "tests/files/unwritable_file.txt: Permission denied", 1, NULL, 1, 3);

	// Test 14: cat < tests/files/empty.txt < tests/files/in.txt > tests/files/out5.txt
	t_tree node14 = {CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "tests/files/empty.txt", &(t_redir){IN_DIR, "tests/files/in.txt", &(t_redir){OUT_DIR, "tests/files/out5.txt", NULL}}}, NULL, NULL};
	helper_orchestrator(14, "cat < tests/files/empty.txt < tests/files/in.txt > tests/files/out5.txt", env, &node14, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, "tests/files/out5.txt", 0, 3);

	// Test 15: cat < tests/files/empty.txt > tests/files/out6.txt < tests/files/in.txt
	t_tree node15 = {CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "tests/files/empty.txt", &(t_redir){OUT_DIR, "tests/files/out6.txt", &(t_redir){IN_DIR, "tests/files/in.txt", NULL}}}, NULL, NULL};
	helper_orchestrator(15, "cat < tests/files/empty.txt > tests/files/out6.txt < tests/files/in.txt", env, &node15, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, "tests/files/out6.txt", 0, 3);

	// Test 16: cat < tests/files/tirade_2.txt >> tests/files/tirade_1.txt
	t_tree node16 = {CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "tests/files/tirade_2.txt", &(t_redir){APPEND_OUT_DIR, "tests/files/tirade_1.txt", NULL}}, NULL, NULL};
	helper_orchestrator(16, "cat < tests/files/tirade_2.txt >> tests/files/tirade_1.txt", env, &node16, "hello\nworld", 0, "tests/files/tirade_1.txt", 0, 3);

	// Test 17: cat << STOP with hello jo
	t_tree node17 = {CMD, (char *[]){"cat", NULL}, &(t_redir){HEREDOC, "hello jo\n", NULL}, NULL, NULL};
	helper_orchestrator(17, "cat << STOP with hello jo", env, &node17, "hello jo\n", 0, NULL, 0, 3);

	// Test 18: cat << STOP (test 1\ntest 2\n) > tests/files/out7.txt
	t_tree node18 = {CMD, (char *[]){"cat", NULL}, &(t_redir){HEREDOC, "test 1 test 2", &(t_redir){OUT_DIR, "tests/files/out7.txt", NULL}}, NULL, NULL};	
	helper_orchestrator(18, "cat << STOP with test 1 test 2\n", env, &node18, "test 1 test 2", 0, "tests/files/out7.txt", 0, 3);

	// Test 19: echo hello > ""
	t_tree node19 = {CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "", NULL}, NULL, NULL};
	helper_orchestrator(19, "echo hello > \"\"", env, &node19, ": No such file or directory", 1, NULL, 1, 3);

	// Test 20: cat ""
	t_tree node20 = {CMD, (char *[]){"cat", "", NULL}, NULL, NULL, NULL};
	helper_orchestrator(20, "cat \"\"", env, &node20, ": No such file or directory", 1, NULL, 1, 3);

	// Test 21: cat >> ""
	t_tree node21 = {CMD, (char *[]){"cat", NULL}, &(t_redir){APPEND_OUT_DIR, "", NULL}, NULL, NULL};
	helper_orchestrator(21, "cat >> \"\"", env, &node21, ": No such file or directory", 1, NULL, 1, 3);

	// Test 22: cat tests/files/in.txt | cat
	t_tree node22 = {CMD, (char *[]){"cat", "tests/files/in.txt", NULL}, NULL, NULL, NULL};
 	t_tree node23 = {CMD, (char *[]){"cat", NULL}, NULL, NULL, NULL};
 	t_tree pipe_node = {PIPE, NULL, NULL, &node22, &node23};
	helper_orchestrator(22, "cat tests/files/in.txt | cat", env, &pipe_node, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, NULL, 0, 3);
}

// void	test_parent_orchestrator(void)
// {

// 	char *env_with_no_path[] = {"HOME=admin", "VAR=abc", NULL};
// 	t_tree node5 = {CMD, (char *[]){"echo", "hello", NULL}, NULL, NULL, NULL};	
// 	actual = cmd_orchestrator(&node5, env_with_no_path, &err);
// 	test_helper(actual, 127, "echo hello with missing PATH in env");

// 	char *no_env[] = {NULL};
// 	t_tree node6 = {CMD, (char *[]){"echo", "hello", NULL}, NULL, NULL, NULL};	
// 	actual = cmd_orchestrator(&node6, no_env, &err);
// 	test_helper(actual, 127, "echo hello with no env");

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
