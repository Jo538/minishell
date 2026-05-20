/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:12:44 by admin             #+#    #+#             */
/*   Updated: 2026/05/20 02:16:39 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd_helper(char **path, char *expected, int test_nb, char *test)
{
	char buffer[100] = {0};

	getcwd(buffer, 100);
	int res = ft_strncmp(buffer, expected, ft_strlen(expected));
	if (res)
		printf("Test %d: --FAIL--\nExpected: %s\nActual: %s\n", test_nb, expected, buffer); // test x: --FAIL--\nexpected: X\nactual:X\n
	else
		printf("Test %d: --SUCCESS-- %s\n", test_nb, test);
	ft_bzero(buffer, 100);
	chdir("/Users/admin/Documents/42/minishell");
}

void test_cd(void)
{
	int test_nb = 1;
	t_error_exec err;

	// Test 1: 'cd src' from project root -->relative path
	char *path1[] = {"cd", "src", NULL};
	run_cd(path1, &err);
	cd_helper(path1, "/Users/admin/Documents/42/minishell/src", test_nb, "'cd src' from project root -->relative path");
	test_nb++;

	// Test 2: 'cd src/executor' from project root --> relative path
	char *path2[] = {"cd", "src/executor", NULL};
	run_cd(path2, &err);
	cd_helper(path2, "/Users/admin/Documents/42/minishell/src/executor", test_nb, "'cd src/executor' from project root --> relative path");
	test_nb++;

	// Test 3: 'cd ..' --> relative path
	char *path3[] = {"cd", "..", NULL};
	run_cd(path3, &err);
	cd_helper(path3, "/Users/admin/Documents/42", test_nb, "'cd ..' --> relative path");
	test_nb++;

	// Test 4: 'cd .' --> relative path
	char *path4[] = {"cd", ".", NULL};
	run_cd(path4, &err);
	cd_helper(path4, "/Users/admin/Documents/42/minishell", test_nb, "'cd .' --> relative path");
	test_nb++;

	// Test 5: 'cd /Users/admin/Documents/42/minishell/src' --> absolute path
	char *path5[] = {"cd", "/Users/admin/Documents/42/minishell/src", NULL};
	run_cd(path5, &err);
	cd_helper(path5, "/Users/admin/Documents/42/minishell/src", test_nb, "'cd /Users/admin/Documents/42/minishell/src' --> absolute path");
	test_nb++;

}

void export_helper(int test_nb, t_env **my_env, char **cmd, char *expected, char *test)
{
	t_error err;
	int fd;
	int copy_fd;
	char path[64];
	char buffer[4096] = {0};

	snprintf(path, sizeof(path), "tests/files/export_%d.txt", test_nb);
	fd = open(path, O_CREAT | O_RDWR, 0644);
	copy_fd = dup(1);
	dup2(fd, 1);
	close(fd);
	run_export(cmd, my_env, &err);
	fflush(stdout);
	lseek(1, 0, SEEK_SET);
	read(1, buffer, 4095);
	if (strcmp(buffer, expected))
	{
		fprintf(stderr, "Test %d --FAIL--%s\nExpected: %s\nActual: %s\n", test_nb, test, expected, buffer); // TEST X --FAIL-- Expected: X Actual: Y
		return ;
	}
	dup2(copy_fd, 1);
	close(copy_fd);
	printf("Test %d --SUCCESS-- %s\n", test_nb, test);
}

void test_export(void)
{
	int test_nb;

	// Test 1: export with empty environment
	test_nb = 1;
	t_env *my_env1[] = {NULL};
	char *cmd1[] = {"export", NULL};
	export_helper(test_nb, my_env1, cmd1, "\0", "export with empty environment");
	
	// export with dense environment
	test_nb = 2;
	t_env *my_env2[] = {&(t_env){"PATH", "/usr/admin", 1, 1}, NULL};
	char *cmd2[] = {"export", NULL};
	export_helper(test_nb, my_env2, cmd2, "export PATH=\"/usr/admin\"\n", "export with dense environment");
	
	// export TEST (TEST doesn't exist)
	test_nb = 3;
	t_env *my_env3[] = {&(t_env){"PATH", "/usr/admin", 1, 1}, NULL};
	char *cmd3[] = {"export", "TEST", NULL};
	export_helper(test_nb, my_env3, cmd3, "export PATH=\"/usr/admin\"\n", "export with dense environment");
	
	// export TEST (TEST already exists)

	// export TEST=abc (TEST doesn't exist)

	// export TEST=abc (TEST already exists)
}