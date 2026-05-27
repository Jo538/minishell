/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 18:57:04 by admin             #+#    #+#             */
/*   Updated: 2026/05/26 22:49:02 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

#define CMD 1
#define PIPE 2

// static int helper_exit_code(int actual, int expected)
// {
// 	if (actual != expected)
// 	{
// 		printf("--FAIL--\nactual: %d\nexpected: %d\n",actual, expected);
// 		return (1);
// 	}
// 	return (0);
// }

// static int helper_output(char *actual, char *expected)
// {
// 	int len = ft_strlen(expected);
// 	if (strncmp(actual, expected, len))
// 	{
// 		printf("--FAIL--\nactual: %s\nexpected: %s\n", actual, expected);
// 		return (1);		
// 	}
// 	return (0);
// }

// static int valgrind_checks(char *array_of_files[], int expected_fds)
// {
// 	int flag_no_fd_issue = 0;
// 	int flag_no_leak = 0;
// 	int flag_no_error = 0;

// 	FILE *fp;
// 	char *line = NULL;
// 	size_t cap = 0;
// 	char path[64];

// 	int i = 0;
// 	while (array_of_files[i])
// 	{
// 		fp = fopen(array_of_files[i], "r");
// 		snprintf(path, sizeof(path), "FILE DESCRIPTORS: %d open", expected_fds);
// 		while (getline(&line, &cap, fp) != -1)
// 		{
// 			if (strstr(line, path))
// 				flag_no_fd_issue = 1;
// 			if (strstr(line, "definitely lost: 0 bytes in 0 blocks"))
// 				flag_no_leak = 1;
// 			if (strstr(line, "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)"))
// 				flag_no_error = 1;			
// 		}
// 		free(line);
// 		fclose(fp);
// 		if (!flag_no_fd_issue || !flag_no_leak || !flag_no_error)
// 		{
// 			printf("%s\n", "--FAIL-- Valgrind error");
// 			return (1);	
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// static char **make_logs_array(glob_t *logs_before)
// {
// 	glob_t logs_after;
// 	int count_before = 0;
// 	int count_after = 0;
// 	int len;

// 	glob("vg*.log", 0, NULL, &logs_after);
// 	while (logs_before->gl_pathv && logs_before->gl_pathv[count_before])
// 		count_before++;
// 	while (logs_after.gl_pathv[count_after])
// 		count_after++;
// 	len = count_after - count_before;
	
// 	char **array = ft_calloc(len + 1, sizeof(char *));
// 	int i = 0;
// 	while (i < len)
// 	{
// 		array[i] = ft_strdup(logs_after.gl_pathv[count_before + i]);
// 		i++;
// 	}
// 	globfree(logs_before);
// 	globfree(&logs_after);	
// 	return (array);
// }

// static int create_output_file(int test_num, char *cmd, char *output_file, int error)
// {
// 	int copy_fd = -1;
// 	int fd;
// 	char path[64];                                                                                                                                                                                                                                                                     

// 	if (output_file)
// 		return (copy_fd);

//   	snprintf(path, sizeof(path), "tests/temp/test_outputs/test_%d.txt", test_num);
// 	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0644);
// 	if (error)
// 	{
// 		copy_fd = dup(2);
// 		dup2(fd, 2);		
// 	}
// 	else
// 	{
// 		copy_fd = dup(1);
// 		dup2(fd, 1);
// 	}
// 	fcntl(copy_fd, F_SETFD, FD_CLOEXEC);
// 	close(fd);
// 	return (copy_fd);
// }

// static char *read_output_file(int test_num, int copy_fd, char *cmd, char *output_file, int error)
// {
// 	int fd;
// 	char path[64];
// 	char buffer[4096] = {0};
// 	char *result;

// 	if (!output_file)
// 	{
// 		snprintf(path, sizeof(path), "tests/temp/test_outputs/test_%d.txt", test_num);
// 		if (error)
// 			dup2(copy_fd, 2);
// 		else
// 			dup2(copy_fd, 1);
// 		close(copy_fd);
// 	}
// 	if (!output_file)
// 		fd = open(path, O_RDONLY);
// 	else
// 		fd = open(output_file, O_RDONLY);
// 	read(fd, buffer, sizeof(buffer) - 1);
// 	result = ft_strdup(buffer);
// 	close(fd);
// 	return (result);
// }

// static void run_checks(int test_num, char *cmd, int actual_exit_code, int expected_exit_code, char *result, char *expected_output, char **array_of_files, int expected_fds)
// {
// 	printf("TEST %d: %s\n", test_num, cmd);
// 	if (!helper_exit_code(actual_exit_code, expected_exit_code)
// 		&& !helper_output(result, expected_output))
// 		printf("%s\n", "--SUCCESS--");
// 	fflush(stdout);
// 	fflush(stderr);		
// }

// static void clean_heap(char **array_of_files, char *result)
// {
// 	int i = 0;
// 	while (array_of_files[i])
// 	{
// 		free(array_of_files[i]);
// 		i++;
// 	}
// 	free(array_of_files);
// 	i = 0;
// 	free(result);	
// }

// static void helper_orchestrator(int test_num, char *cmd, char **env, t_tree *node, char *expected_output, int expected_exit_code, char *output_file, int error, int expected_fds)
// {
// 	int actual_exit_code;
// 	char *result = NULL;

// 	glob_t logs_before = {0};
	
    
// 	int copy_fd = create_output_file(test_num, cmd, output_file, error);
// 	//glob("vg*.log", 0, NULL, &logs_before);
// 	actual_exit_code = execute(node, env);
// 	char **array_of_files = make_logs_array(&logs_before);
// 	result = read_output_file(test_num, copy_fd, cmd, output_file, error);
// 	run_checks(test_num, cmd, actual_exit_code, expected_exit_code, result, expected_output, array_of_files, expected_fds);
// 	clean_heap(array_of_files, result);
// }

t_env	**make_env(t_env **my_env)
{
	int i = 0;
	int	size = 0;
	t_env **new_env;
	
	while (my_env[size])
		size++;
	new_env = ft_calloc(size + 1, sizeof(t_env *));
	while (my_env[i])
	{
		new_env[i] = ft_calloc(1, sizeof(t_env));
		new_env[i]->key = ft_strdup(my_env[i]->key);
		new_env[i]->value = ft_strdup(my_env[i]->value);
		new_env[i]->export_flag = my_env[i]->export_flag;
		new_env[i]->set_flag = my_env[i]->set_flag;
		i++;
	}
	return (new_env);
}

t_redir *make_redirections(t_redir *new_head, t_redir *head)
{
	new_head = ft_calloc(1, sizeof(t_redir));
	t_redir	*tmp = new_head;
	while (head)
	{
		tmp->type = head->type;
		tmp->file = ft_strdup(head->file);	
		if (head->next)
		 tmp->next = ft_calloc(1, sizeof(t_redir));
		tmp = tmp->next;	
		head = head->next;				
	}
	return (new_head);
}

t_tree *make_node(t_tree *node)
{
	t_tree *new_node;
	int size = 0;
	int i = 0;
	new_node = ft_calloc(1, sizeof(t_tree));
	if (node->type == NODE_CMD)
	{
		while (node->argv[size])
			size++;
		new_node->argv = ft_calloc(size + 1, sizeof(char *));
		while (node->argv[i])
		{
			new_node->argv[i] = ft_strdup(node->argv[i]);
			i++;
		}		
	}
	if (node->redirections)
		new_node->redirections = make_redirections(new_node->redirections, node->redirections);
	if (node->type == NODE_PIPE)
	{
		new_node->left = node->left;
		new_node->right = node->right;
	}
	new_node->type = node->type;
	return (new_node);
}

void test_improved_version_executor(void)
{
	int exit_code = 0;
	// int copy_fd1;
	// int fd;
	// int actual;
	// char buffer[4096] = {0};
	// glob_t logs_before;

	//create temp folder and test_outputs folder
	// system("mkdir -p tests/temp/test_outputs");

	// create malloc'd env
	t_env *my_env[] = {&(t_env){"HOME", "admin", 1, 1}, &(t_env){"PATH", "/local/sbin:/local/bin:/bin:/usr/bin", 1, 1}, NULL};
	t_env **env = make_env(my_env);

	// Test 1: echo hello
	printf("\n--TEST 1--%s", "echo hello\n");
	t_tree *node1 = make_node(&(t_tree){NODE_CMD, (char *[]){"echo", "hello", NULL}, NULL, NULL, NULL});
	executor(node1, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node1);
	// helper_orchestrator(1, "echo hello", env, &node1, "hello", 0, NULL, 0, 3);

	// // Test 2: /bin/echo hello
	printf("\n--TEST 2--%s", "/bin/echo hello\n");
	t_tree *node2 = make_node(&(t_tree){NODE_CMD, (char *[]){"/bin/echo", "hello", NULL}, NULL, NULL, NULL});	
	executor(node2, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node2);
	// helper_orchestrator(2, "/bin/echo hello", env, &node2, "hello", 0, NULL, 0, 3);

	// Test 3: echoo hello
	printf("\n--TEST 3--%s", "echoo hello\n");
	t_tree *node3 = make_node(&(t_tree){NODE_CMD, (char *[]){"echoo", "hello", NULL}, NULL, NULL, NULL});
	executor(node3, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node3);	
	// helper_orchestrator(3, "echoo hello", env, &node3, "echoo: Command not found", 127, NULL, 1, 4);

	exit_code = 0;

	// Test 4: /bin/echoo hello
	printf("\n--TEST 4--%s", "/bin/echoo hello\n");
	t_tree *node4 = make_node(&(t_tree){NODE_CMD, (char *[]){"/bin/echoo", "hello", NULL}, NULL, NULL, NULL});
	executor(node4, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node4);
	// helper_orchestrator(4, "echoo hello", env, &node4, "/bin/echoo: No such file or directory", 127, NULL, 1, 4);

	exit_code = 0;

	// Test 5: tests/files/unreadable_file.txt hello
	printf("\n--TEST 5--%s", "tests/files/unreadable_file.txt hello\n");
	t_tree *node5 = make_node(&(t_tree){NODE_CMD, (char *[]){"tests/files/unreadable_file.txt", "hello", NULL}, NULL, NULL, NULL});
	executor(node5, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node5);
	// helper_orchestrator(5, "tests/files/unreadable_file.txt hello", env, &node5, "tests/files/unreadable_file.txt: Permission denied", 126, NULL, 1, 4);

	exit_code = 0;
	
	// Test 6 cat < tests/files/in.txt
	printf("\n--TEST 6--%s", "cat < tests/files/in.txt\n");
	t_tree *node6 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "tests/files/in.txt", NULL}, NULL, NULL});
	executor(node6, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node6);
	// helper_orchestrator(6, "cat < tests/files/in.txt", env, &node6, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, NULL, 0, 3);

	// Test 7: echo hello > tests/files/out.txt
	printf("\n--TEST 7--%s", "echo hello > tests/files/out.txt\n");
	t_tree *node7 = make_node(&(t_tree){NODE_CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/out.txt", NULL}, NULL, NULL});
	executor(node7, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node7);
	// helper_orchestrator(7, "echo hello > tests/files/out.txt", env, &node7, "hello", 0, "tests/files/out.txt", 0, 3);

	// Test 8: echo hello > tests/files/nonexistent_out.txt
	printf("\n--TEST 8--%s", "echo hello > tests/files/nonexistent_out.txt\n");
	t_tree *node8 = make_node(&(t_tree){NODE_CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/nonexistent_out.txt", NULL}, NULL, NULL});
	executor(node8, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node8);
	// helper_orchestrator(8, "echo hello > tests/files/nonexistent_out.txt", env, &node8, "hello", 0, "tests/files/nonexistent_out.txt", 0, 3);

	// Test 9: cat < tests/files/unreadable_file.txt
	printf("\n--TEST 9--%s", "cat < tests/files/unreadable_file.txt\n");
	t_tree *node9 = make_node(&(t_tree){NODE_CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){IN_DIR, "tests/files/unreadable_file.txt", NULL}, NULL, NULL});
	executor(node9, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node9);
	// helper_orchestrator(9, "cat < tests/files/unreadable_file.txt", env, &node9, "tests/files/unreadable_file.txt: Permission denied", 1, NULL, 1, 3);

	// Test 10: echo hello > tests/files/unwritable_file.txt
	printf("\n--TEST 10--%s", "echo hello > tests/files/unwritable_file.txt\n");
	t_tree *node10 = make_node(&(t_tree){NODE_CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/unwritable_file.txt", NULL}, NULL, NULL});
	executor(node10, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node10);
	// helper_orchestrator(10, "echo hello > tests/files/unwritable_file.txt", env, &node10, "tests/files/unwritable_file.txt: Permission denied", 1, NULL, 1, 3);

	exit_code = 0;

	// Test 11: echo hello > tests/files/out.txt > tests/files/out1.txt
	printf("\n--TEST 11--%s", "echo hello > tests/files/out.txt > tests/files/out1.txt\n");
	t_tree *node11 = make_node(&(t_tree){NODE_CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/out.txt", &(t_redir){OUT_DIR, "tests/files/out1.txt", NULL}}, NULL, NULL});
	executor(node11, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node11);
	// helper_orchestrator(11, "echo Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap ! > tests/files/out.txt > tests/files/out1.txt", env, &node11, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, "tests/files/out1.txt", 1, 3);

	exit_code = 0;
	
	// Test 12: cat tests/files/tirade_1.txt > tests/files/out2.txt > tests/files/out3.txt
	printf("\n--TEST 12--%s", "cat tests/files/tirade_1.txt > tests/files/out2.txt > tests/files/out3.txt\n");
	t_tree *node12 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", "tests/files/tirade_1.txt", NULL}, &(t_redir){OUT_DIR, "tests/files/out2.txt", &(t_redir){OUT_DIR, "tests/files/out3.txt", NULL}}, NULL, NULL});
	executor(node12, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node12);
	// helper_orchestrator(12, "echo Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap ! > tests/files/out2.txt > tests/files/out3.txt", env, &node12, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, "tests/files/out3.txt", 1, 3);

	exit_code = 0;
	
	// Test 13: echo hello > tests/files/unwritable_file.txt > tests/files/out4.txt
	printf("\n--TEST 13--%s", "echo hello > tests/files/unwritable_file.txt > tests/files/out4.txt\n");
	t_tree *node13 = make_node(&(t_tree){NODE_CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "tests/files/unwritable_file.txt", &(t_redir){OUT_DIR, "tests/files/out4.txt", NULL}}, NULL, NULL});
	executor(node13, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node13);
	// helper_orchestrator(13, "echo hello > tests/files/unwritable_file.txt > tests/files/out4.txt", env, &node13, "tests/files/unwritable_file.txt: Permission denied", 1, NULL, 1, 3);

	exit_code = 0;
	
	// Test 14: cat < tests/files/empty.txt < tests/files/in.txt > tests/files/out5.txt
	printf("\n--TEST 14--%s", "cat < tests/files/empty.txt < tests/files/in.txt > tests/files/out5.txt\n");
	t_tree *node14 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "tests/files/empty.txt", &(t_redir){IN_DIR, "tests/files/in.txt", &(t_redir){OUT_DIR, "tests/files/out5.txt", NULL}}}, NULL, NULL});
	executor(node14, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node14);
	// helper_orchestrator(14, "cat < tests/files/empty.txt < tests/files/in.txt > tests/files/out5.txt", env, &node14, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, "tests/files/out5.txt", 0, 3);

	// Test 15: cat < tests/files/empty.txt > tests/files/out6.txt < tests/files/in.txt
	printf("\n--TEST 15--%s", "cat < tests/files/empty.txt > tests/files/out6.txt < tests/files/in.txt\n");
	t_tree *node15 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "tests/files/empty.txt", &(t_redir){OUT_DIR, "tests/files/out6.txt", &(t_redir){IN_DIR, "tests/files/in.txt", NULL}}}, NULL, NULL});
	executor(node15, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node15);
	// helper_orchestrator(15, "cat < tests/files/empty.txt > tests/files/out6.txt < tests/files/in.txt", env, &node15, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, "tests/files/out6.txt", 0, 3);

	// Test 16: cat < tests/files/tirade_2.txt >> tests/files/tirade_1.txt
	printf("\n--TEST 16--%s", "cat < tests/files/tirade_2.txt >> tests/files/tirade_1.txt\n");
	t_tree *node16 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "tests/files/tirade_2.txt", &(t_redir){APPEND_OUT_DIR, "tests/files/tirade_1.txt", NULL}}, NULL, NULL});
	executor(node16, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node16);
	
	// helper_orchestrator(16, "cat < tests/files/tirade_2.txt >> tests/files/tirade_1.txt", env, &node16, "hello\nworld", 0, "tests/files/tirade_1.txt", 0, 3);

	// Test 17: cat << STOP with hello jo
	printf("\n--TEST 17--%s", "cat << STOP with hello jo\n");
	t_tree *node17 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, &(t_redir){HEREDOC, "hello jo\n", NULL}, NULL, NULL});
	executor(node17, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node17);
	// helper_orchestrator(17, "cat << STOP with hello jo", env, &node17, "hello jo\n", 0, NULL, 0, 3);

	// Test 18: cat << STOP (test 1\ntest 2\n) > tests/files/out7.txt
	printf("\n--TEST 18--%s", "cat << STOP (test 1 test 2) > tests/files/out7.txt\n");
	t_tree *node18 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, &(t_redir){HEREDOC, "test 1\ntest 2", &(t_redir){OUT_DIR, "tests/files/out7.txt", NULL}}, NULL, NULL});	
	executor(node18, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node18);
	// helper_orchestrator(18, "cat << STOP with test 1 test 2\n", env, &node18, "test 1 test 2", 0, "tests/files/out7.txt", 0, 3);

	// Test 19: echo hello > ""
	printf("\n--TEST 19--%s", "echo hello > ""\n");
	t_tree *node19 = make_node(&(t_tree){NODE_CMD, (char *[]){"echo", "hello", NULL}, &(t_redir){OUT_DIR, "", NULL}, NULL, NULL});
	executor(node19, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node19);
	// helper_orchestrator(19, "echo hello > \"\"", env, &node19, ": No such file or directory", 1, NULL, 1, 3);

	exit_code = 0;
	
	// Test 20: cat ""
	printf("\n--TEST 20--%s", "cat ""\n");
	t_tree *node20 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", "", NULL}, NULL, NULL, NULL});
	executor(node20, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node20);
	// helper_orchestrator(20, "cat \"\"", env, &node20, ": No such file or directory", 1, NULL, 1, 3);

	exit_code = 0;
	
	// Test 21: cat >> ""
	printf("\n--TEST 21--%s", "cat >> ""\n");
	t_tree *node21 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, &(t_redir){APPEND_OUT_DIR, "", NULL}, NULL, NULL});
	executor(node21, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(node21);
	// helper_orchestrator(21, "cat >> \"\"", env, &node21, ": No such file or directory", 1, NULL, 1, 3);

	exit_code = 0;

	// Test 22: cat tests/files/in.txt | cat
	printf("\n--TEST 22--%s", "cat tests/files/in.txt | cat\n");
	t_tree *node22 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", "tests/files/in.txt", NULL}, NULL, NULL, NULL});
 	t_tree *node23 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, NULL, NULL, NULL});
 	t_tree *pipe_node = make_node(&(t_tree){NODE_PIPE, NULL, NULL, NULL, node22, node23});
	executor(pipe_node, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(pipe_node);
	// helper_orchestrator(22, "cat tests/files/in.txt | cat", env, &pipe_node, "Descriptif : « C’est un roc ! … c’est un pic ! … c’est un cap !", 0, NULL, 0, 3);

	// TEST 23: cat Makefile | wc -l
	printf("\n--TEST 23--%s", "cat Makefile | wc -l\n");
	t_tree *node24 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", "Makefile", NULL}, NULL, NULL, NULL});
 	t_tree *node25 = make_node(&(t_tree){NODE_CMD, (char *[]){"wc", "-l", NULL}, NULL, NULL, NULL});
 	t_tree *pipe_node1 = make_node(&(t_tree){NODE_PIPE, NULL, NULL, NULL, node24, node25});
	executor(pipe_node1, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(pipe_node1);
	
	// Test 24: catt Makefile | wc -l
	printf("\n--TEST 24--%s", "catt Makefile | wc -l\n");
	t_tree *node26 = make_node(&(t_tree){NODE_CMD, (char *[]){"catt", "Makefile", NULL}, NULL, NULL, NULL});
 	t_tree *node27 = make_node(&(t_tree){NODE_CMD, (char *[]){"wc", "-l", NULL}, NULL, NULL, NULL});
 	t_tree *pipe_node2 = make_node(&(t_tree){NODE_PIPE, NULL, NULL, NULL, node26, node27});
	executor(pipe_node2, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(pipe_node2);

	exit_code = 0;
	
	// Test 25: cat Makefile | wcc -l
	printf("\n--TEST 25--%s", "cat Makefile | wcc -l\n");
	t_tree *node28 = make_node(&(t_tree){CMD, (char *[]){"cat", "Makefile", NULL}, NULL, NULL, NULL});
 	t_tree *node29 = make_node(&(t_tree){CMD, (char *[]){"wcc", "-l", NULL}, NULL, NULL, NULL});
 	t_tree *pipe_node3 = make_node(&(t_tree){PIPE, NULL, NULL, NULL, node28, node29});
	executor(pipe_node3, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(pipe_node3);

	exit_code = 0;
	
	// Test 26: cat Makefile | wcc -l
	printf("\n--TEST 26--%s", "cat < Makefiles | wc -l\n");
 	t_tree *node30 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, &(t_redir){IN_DIR, "Makefiles", NULL}, NULL, NULL});
 	t_tree *node31 = make_node(&(t_tree){NODE_CMD, (char *[]){"wc", "-l", NULL}, NULL, NULL, NULL});
 	t_tree *pipe_node4 = make_node(&(t_tree){NODE_PIPE, NULL, NULL, NULL, node30, node31});
	executor(pipe_node4, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(pipe_node4);

	exit_code = 0;
	
	// Test 27: cat Makefile | cat | cat > tests/files/out8.txt
	printf("\n--TEST 27--%s", "cat Makefile | cat | cat > tests/files/out8.txt\n");
	t_tree *inner_pipe_left_node = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", "Makefile", NULL}, NULL, NULL, NULL});
 	t_tree *inner_pipe_right_node = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, NULL, NULL, NULL});
 	t_tree *inner_pipe = make_node(&(t_tree){NODE_PIPE, NULL, NULL, NULL, inner_pipe_left_node, inner_pipe_right_node});
	
	t_tree *outer_pipe_right_node = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, &(t_redir){OUT_DIR, "tests/files/out8.txt", NULL}, NULL, NULL});
	t_tree *outer_pipe = make_node(&(t_tree){NODE_PIPE, NULL, NULL, NULL, inner_pipe, outer_pipe_right_node});
	executor(outer_pipe, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(outer_pipe);

	
	// Test 28: cat Makefile | cats | cat > tests/files/out9.txt
	printf("\n--TEST 28--%s", "cat Makefile | cats | cat > tests/files/out9.txt\n");
	t_tree *inner_pipe_left_node1 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", "Makefile", NULL}, NULL, NULL, NULL});
 	t_tree *inner_pipe_right_node1 = make_node(&(t_tree){NODE_CMD, (char *[]){"cats", NULL}, NULL, NULL, NULL});
 	t_tree *inner_pipe1 = make_node(&(t_tree){NODE_PIPE, NULL, NULL, NULL, inner_pipe_left_node1, inner_pipe_right_node1});
	
	t_tree *outer_pipe_right_node1 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, &(t_redir){OUT_DIR, "tests/files/out9.txt", NULL}, NULL, NULL});
	t_tree *outer_pipe1 = make_node(&(t_tree){NODE_PIPE, NULL, NULL, NULL, inner_pipe1, outer_pipe_right_node1});
	executor(outer_pipe1, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(outer_pipe1);

	// Test 29: cat Makefile | cat | cats > tests/files/out9.txt
	printf("\n--TEST 29--%s", "cat Makefile | cat | cats > tests/files/out9.txt\n");
	t_tree *inner_pipe_left_node2 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", "Makefile", NULL}, NULL, NULL, NULL});
 	t_tree *inner_pipe_right_node2 = make_node(&(t_tree){NODE_CMD, (char *[]){"cat", NULL}, NULL, NULL, NULL});
 	t_tree *inner_pipe2 = make_node(&(t_tree){NODE_PIPE, NULL, NULL, NULL, inner_pipe_left_node2, inner_pipe_right_node2});
	
	t_tree *outer_pipe_right_node2 = make_node(&(t_tree){NODE_CMD, (char *[]){"cats", NULL}, &(t_redir){OUT_DIR, "tests/files/out9.txt", NULL}, NULL, NULL});
	t_tree *outer_pipe2 = make_node(&(t_tree){NODE_PIPE, NULL, NULL, NULL, inner_pipe2, outer_pipe_right_node2});
	executor(outer_pipe2, env, &exit_code);
	printf("exit code: %d\n", exit_code);
	free_node(outer_pipe2);

	exit_code = 0;	

	void	print_var(t_env **my_env);

 	// Test 30: export TEST
	printf("\n--TEST 30--%s", "export TEST\n");
	t_tree *node32 = make_node(&(t_tree){NODE_CMD, (char *[]){"export", "TEST", NULL}, NULL, NULL, NULL});
	env = executor(node32, env, &exit_code);
	print_var(env);
	printf("exit code: %d\n", exit_code);
	free_node(node32);

	
	// Test 31: export TEST > tests/files/out10.txt
	printf("\n--TEST 31--%s", "export TEST > tests/files/out10.txt\n");
	t_tree *node33 = make_node(&(t_tree){NODE_CMD, (char *[]){"export", "TEST1", NULL}, &(t_redir){OUT_DIR, "tests/files/out10.txt", NULL}, NULL, NULL});
	env = executor(node33, env, &exit_code);
	print_var(env);
	printf("exit code: %d\n", exit_code);
	free_node(node33);

	// Test 32: export TEST > tests/files/out10.txt > tests/files/out11.txt
	printf("\n--TEST 32--%s", "export TEST > tests/files/out10.txt > tests/files/out11.txt\n");
	t_tree *node34 = make_node(&(t_tree){NODE_CMD, (char *[]){"export", "TEST2", NULL}, &(t_redir){OUT_DIR, "tests/files/out10.txt", &(t_redir){OUT_DIR, "tests/files/out11.txt", NULL}}, NULL, NULL});
	env = executor(node34, env, &exit_code);
	print_var(env);
	printf("exit code: %d\n", exit_code);
	free_node(node34);

	// Test 33: export TEST < tests/files/in.txt > tests/files/out12.txt
	printf("\n--TEST 33--%s", "export TEST < tests/files/in.txt > tests/files/out12.txt\n");
	t_tree *node35 = make_node(&(t_tree){NODE_CMD, (char *[]){"export", "TEST3", NULL}, &(t_redir){IN_DIR, "tests/files/in.txt", &(t_redir){OUT_DIR, "tests/files/out12.txt", NULL}}, NULL, NULL});
	env = executor(node35, env, &exit_code);
	print_var(env);
	printf("exit code: %d\n", exit_code);
	free_node(node35);

	free_my_env(env);
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

// 	t_tree node2 = {CMD, (char *[]){"/bin/cat", "Makefile", NULL}, NULL, NULL, NULL};
// 	t_tree node3 = {CMD, (char *[]){"wc", "-l", NULL}, NULL, NULL, NULL};
// 	t_tree pipe_node1 = {PIPE, NULL, NULL, &node2, &node3};
// 	actual = pipe_orchestrator(&pipe_node1, env, &err);
// 	test_helper(actual, 0, "/bin/cat Makefile | wc -l");

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
