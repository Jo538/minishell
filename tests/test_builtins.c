/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:12:44 by admin             #+#    #+#             */
/*   Updated: 2026/05/18 21:41:37 by admin            ###   ########.fr       */
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