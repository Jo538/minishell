// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test_builtins.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/05/18 14:12:44 by admin             #+#    #+#             */
// /*   Updated: 2026/05/20 23:38:49 by admin            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void cd_helper(char **path, char *expected, int test_nb, char *test)
// {
// 	char buffer[100] = {0};

// 	getcwd(buffer, 100);
// 	int res = ft_strncmp(buffer, expected, ft_strlen(expected));
// 	if (res)
// 		printf("Test %d: --FAIL--\nExpected: %s\nActual: %s\n", test_nb, expected, buffer); // test x: --FAIL--\nexpected: X\nactual:X\n
// 	else
// 		printf("Test %d: --SUCCESS-- %s\n", test_nb, test);
// 	ft_bzero(buffer, 100);
// 	chdir("/Users/admin/Documents/42/minishell");
// }

// void test_cd(void)
// {
// 	int test_nb = 1;
// 	t_error_exec err;

// 	// Test 1: 'cd src' from project root -->relative path
// 	char *path1[] = {"cd", "src", NULL};
// 	run_cd(path1, &err);
// 	cd_helper(path1, "/Users/admin/Documents/42/minishell/src", test_nb, "'cd src' from project root -->relative path");
// 	test_nb++;

// 	// Test 2: 'cd src/executor' from project root --> relative path
// 	char *path2[] = {"cd", "src/executor", NULL};
// 	run_cd(path2, &err);
// 	cd_helper(path2, "/Users/admin/Documents/42/minishell/src/executor", test_nb, "'cd src/executor' from project root --> relative path");
// 	test_nb++;

// 	// Test 3: 'cd ..' --> relative path
// 	char *path3[] = {"cd", "..", NULL};
// 	run_cd(path3, &err);
// 	cd_helper(path3, "/Users/admin/Documents/42", test_nb, "'cd ..' --> relative path");
// 	test_nb++;

// 	// Test 4: 'cd .' --> relative path
// 	char *path4[] = {"cd", ".", NULL};
// 	run_cd(path4, &err);
// 	cd_helper(path4, "/Users/admin/Documents/42/minishell", test_nb, "'cd .' --> relative path");
// 	test_nb++;

// 	// Test 5: 'cd /Users/admin/Documents/42/minishell/src' --> absolute path
// 	char *path5[] = {"cd", "/Users/admin/Documents/42/minishell/src", NULL};
// 	run_cd(path5, &err);
// 	cd_helper(path5, "/Users/admin/Documents/42/minishell/src", test_nb, "'cd /Users/admin/Documents/42/minishell/src' --> absolute path");
// 	test_nb++;

// }

// t_env **export_helper(int test_nb, t_env **my_env, char **cmd, char *expected, char *test, int expected_set, int expected_export)
// {
// 	t_error err = 0;
// 	int fd;
// 	int copy_fd;
// 	char path[64];
// 	char buffer[4096] = {0};

// 	snprintf(path, sizeof(path), "tests/files/export_%d.txt", test_nb);
// 	fd = open(path, O_CREAT | O_RDWR, 0644);
// 	copy_fd = dup(1);
// 	dup2(fd, 1);
// 	close(fd);
// 	my_env = run_export(cmd, my_env, &err);
// 	fflush(stdout);
// 	char *cmd2[] = {"export", NULL};
// 	if (cmd[1])
// 		run_export(cmd2, my_env, &err); // char *cmd[] -> {}
// 	fflush(stdout);
// 	lseek(1, 0, SEEK_SET);
// 	read(1, buffer, 4095);
// 	if (strcmp(buffer, expected))
// 	{
// 		fprintf(stderr, "Test %d --FAIL--%s\nExpected: %s\nActual: %s\n", test_nb, test, expected, buffer); // TEST X --FAIL-- Expected: X Actual: Y
// 		return (my_env);
// 	}
// 	if (expected_export != -1 && my_env[1]->export_flag != expected_export)
// 	{
// 		fprintf(stderr, "Test %d --FAIL--%s\nExpected: %d\nActual: %d\n", test_nb, test, expected_export, my_env[1]->export_flag); // TEST X --FAIL-- Expected: X Actual: Y
// 		return (my_env);
// 	}	
// 	if (expected_set != -1 && my_env[1]->set_flag != expected_set)
// 	{
// 		fprintf(stderr, "Test %d --FAIL--%s\nExpected: %d\nActual: %d\n", test_nb, test, expected_set, my_env[1]->set_flag); // TEST X --FAIL-- Expected: X Actual: Y
// 		return (my_env);
// 	}		
// 	dup2(copy_fd, 1);
// 	close(copy_fd);
// 	printf("Test %d --SUCCESS-- %s\n", test_nb, test);
// 	fflush(stdout);
// 	return (my_env);
// }

// void test_export(void)
// {
// 	fflush(stdout);
// 	int test_nb;

// 	// Test 1: export with empty environment
// 	test_nb = 1;
// 	t_env *my_env1[] = {NULL};
// 	char *cmd1[] = {"export", NULL};
// 	export_helper(test_nb, my_env1, cmd1, "\0", "export with empty environment", -1, -1);
	
// 	// export with dense environment
// 	test_nb = 2;
// 	t_env *my_env2[] = {&(t_env){"PATH", "/usr/admin", 1, 1}, NULL};
// 	char *cmd2[] = {"export", NULL};
// 	export_helper(test_nb, my_env2, cmd2, "export PATH=\"/usr/admin\"\n", "export with dense environment", -1, -1);
	
// 	// export TEST (TEST doesn't exist)
// 	test_nb = 3;
// 	t_env **my_env3 = calloc(2, sizeof(t_env *)); // {&(t_env){"PATH", "/usr/admin", 1, 1}, NULL};
// 	*my_env3 = calloc(1, sizeof(t_env));
// 	(*my_env3)->key = ft_strdup("PATH");
// 	(*my_env3)->value = ft_strdup("/usr/admin");
// 	(*my_env3)->export_flag = 1;
// 	(*my_env3)->set_flag = 1;
// 	char *cmd3[] = {"export", "TEST", NULL};
// 	my_env3 = export_helper(test_nb, my_env3, cmd3, "export PATH=\"/usr/admin\"\nexport TEST\n", "export TEST (TEST doesn't exist)", 0, 1);
	
// 	// export TEST (TEST already exists)
// 	test_nb = 4;
// 	my_env3 = export_helper(test_nb, my_env3, cmd3, "export PATH=\"/usr/admin\"\nexport TEST\n", "export TEST (TEST already exists)", 0, 1);
	
// 	// export TEST1=abc (TEST doesn't exist)
// 	test_nb = 5;
// 	char *cmd5[] = {"export", "TEST=abc", NULL};
// 	my_env3 = export_helper(test_nb, my_env3, cmd5, "export PATH=\"/usr/admin\"\nexport TEST=\"abc\"\n", "export TEST1=abc (TEST1 doesn't exist)", 1, 1);
	
// 	// export TEST1 TEST2
// 	test_nb = 6;
// 	char *cmd6[] = {"export", "TEST1", "TEST2", NULL};
// 	my_env3 = export_helper(test_nb, my_env3, cmd6, "export PATH=\"/usr/admin\"\nexport TEST=\"abc\"\nexport TEST1\nexport TEST2\n", "export TEST1 TEST2", 1, 1);
		
// 	free_my_env(my_env3);
// }

// static int	open_redirections(int test_nb)
// {
// 	fflush(stdout);
// 	int copy_fd;
// 	char path[64];

// 	copy_fd = dup(1);
// 	snprintf(path, sizeof(path), "tests/files/unset_%d.txt", test_nb);
// 	int fd = open(path, O_CREAT | O_RDWR, 0644);
// 	dup2(fd, 1);
// 	close(fd);
// 	return (copy_fd);
// }

// static void write_to_file(t_env **my_env)
// {
// 	int	i = 0;

// 	while (my_env[i])
// 	{
// 		printf("%s\n%s\n", my_env[i]->key, my_env[i]->value);
// 		i++;
// 	}
// 	fflush(stdout);
// }

// static int	close_redirections(int copy_fd)
// {
// 	int fd = dup(1);
// 	dup2(copy_fd, 1);
// 	close(copy_fd);
// 	return (fd);
// }

// static void unset_helper(t_env **my_env, char *expected, int test_nb, char *test)
// {
// 	char buffer[4096] = {0};
	
// 	int copy_fd = open_redirections(test_nb);
// 	write_to_file(my_env);
	
// 	int fd = close_redirections(copy_fd);
// 	lseek(fd, 0, SEEK_SET);
// 	read(fd, buffer, 4095);
// 	if (strcmp(buffer, expected))
// 		fprintf(stderr, "Test %d --FAIL--%s\nExpected: %s\nActual: %s\n", test_nb, test, expected, buffer); // TEST X --FAIL-- Expected: X Actual: Y
// 	else
// 		printf("Test %d --SUCCESS-- %s\n", test_nb, test);
// 	fflush(stdout);
// 	close(fd);
	
// }

// void test_unset(void)
// {
// 	t_error err = 0;
// 	int test_nb = 1;

// 	// Test 1: unset TEST (TEST exists)
// 	char *cmd1[] = {"unset", "TEST", NULL};
// 	t_env **my_env1 = calloc(3, sizeof(t_env *)); // {&(t_env){"PATH", "/usr/admin", 1, 1}, NULL};
// 	*my_env1 = calloc(1, sizeof(t_env));
// 	(*my_env1)->key = ft_strdup("PATH");
// 	(*my_env1)->value = ft_strdup("/usr/admin");
// 	*(my_env1 + 1) = calloc(1, sizeof(t_env));
// 	(*(my_env1 + 1))->key = ft_strdup("TEST");
// 	(*(my_env1 + 1))->value = ft_strdup("abc");

// 	my_env1 = run_unset(cmd1, my_env1, &err);
// 	unset_helper(my_env1, "PATH\n/usr/admin\n", test_nb, "unset TEST (TEST exists)");

// 	// TEST 2: unset
// 	test_nb = 2;
// 	char *cmd2[] = {"unset", NULL};
// 	my_env1 = run_unset(cmd2, my_env1, &err);
// 	unset_helper(my_env1, "PATH\n/usr/admin\n", test_nb, "unset");

// 	// TEST 3: unset TEST (TEST doesn't exist)
// 	test_nb = 3;
// 	char *cmd3[] = {"unset", "TEST", NULL};
// 	my_env1 = run_unset(cmd3, my_env1, &err);
// 	unset_helper(my_env1, "PATH\n/usr/admin\n", test_nb, "unset TEST (TEST doesn't exist)");

// 	free_my_env(my_env1);

// 	// TEST 4: unset TEST TEST1 (both exist)
// 	test_nb = 4;
// 	char *cmd4[] = {"unset", "TEST", "TEST1", NULL};
// 	t_env **my_env2 = calloc(4, sizeof(t_env *)); // {&(t_env){"PATH", "/usr/admin", 1, 1}, NULL};
// 	*my_env2 = calloc(1, sizeof(t_env));
// 	(*my_env2)->key = ft_strdup("PATH");
// 	(*my_env2)->value = ft_strdup("/usr/admin");
// 	*(my_env2 + 1) = calloc(1, sizeof(t_env));
// 	(*(my_env2 + 1))->key = ft_strdup("TEST");
// 	*(my_env2 + 2) = calloc(1, sizeof(t_env));
// 	(*(my_env2 + 2))->key = ft_strdup("TEST1");

// 	my_env2 = run_unset(cmd4, my_env2, &err);
// 	unset_helper(my_env2, "PATH\n/usr/admin\n", test_nb, "unset TEST TEST1 (both exist)");
	
// 	free_my_env(my_env2);
// }