/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 11:12:25 by admin             #+#    #+#             */
/*   Updated: 2026/04/28 16:40:08 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void	helper_test_extract_paths(char **actual, char **expected)
{
	int i = 0;

	if (!expected)
	{
		if (expected != actual)
			printf("--FAIL--\nactual: %p\nexpected: %p\n", actual, expected);
		printf("%s\n", "--SUCCESS--");
		return ;
	}
	while (expected[i])
	{
		if (strcmp(actual[i], expected[i]))
		{
			printf("--FAIL--\nactual: %s\nexpected: %s\n", actual[i], expected[i]);
			return ;
		}
		i++;	
	}
	free_tab(actual);
	printf("%s\n", "--SUCCESS--");
}

void	test_extract_paths(void)
{
	t_error err = 0;
	char **path_tab = NULL;

	char **env[] = {
		NULL,
		(char *[]){NULL},
		(char *[]){"", NULL},
		(char *[]){"HOME=abc", "VAR=def", NULL},
		(char *[]){"HOME=abc", "VAR=def", "PATH=/bin:/local/sbin:/homebrew/bin", NULL}
	};

	char **expected[] = {
		NULL,
		NULL,
		NULL,
		NULL,
		(char *[]){"/bin", "/local/sbin", "/homebrew/bin", NULL}		
	};
	
	int i = 0;

	while (i < 5)
	{
		path_tab = extract_paths(env[i], &err);
		helper_test_extract_paths(path_tab, expected[i]);
		i++;		
	}
}

static void	helper_test_find_and_check_path(char *actual, char *expected)
{
	int i = 0;

	if (!expected)
	{
		if (expected != actual)
			printf("--FAIL--\nactual: %p\nexpected: %p\n", actual, expected);
		printf("%s\n", "--SUCCESS--");
		return ;
	}
	if (strcmp(actual, expected))
	{
		printf("--FAIL--\nactual: %s\nexpected: %s\n", actual, expected);
		free(actual);
		return ;
	}
	free(actual);
	printf("%s\n", "--SUCCESS--");
}

void test_find_and_check_path(void)
{
	t_error err = 0;
	char *path = NULL;
	
	t_test_path pairs[] = {
		{NULL, NULL},
		{NULL, (char *[]){"/usr/local", "local/sbin", "/bin", NULL}},
		{"", NULL},
		{"", (char *[]){"/usr/local", "local/sbin", "/bin", NULL}},
		{"catt", NULL},
		{"catt", (char *[]){"/usr/local", "local/sbin", "/bin", NULL}},
		{"cat", NULL},
		{"cat", (char *[]){"/usr/local", "local/sbin", "/bin", NULL}}
	};

	char *expected[] = {
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		(char *){"/bin/cat"}
	};

	int i = 0;
	while (i < 8)
	{
		path = find_and_check_path(pairs[i].cmd, pairs[i].path_tab, &err);
		helper_test_find_and_check_path(path, expected[i]);
		i++;
	}
}

static void	helper_test_path_orchestrator(char *actual, char *expected)
{
	int i = 0;

	if (!expected)
	{
		if (expected != actual)
			printf("--FAIL--\nactual: %p\nexpected: %p\n", actual, expected);
		printf("%s\n", "--SUCCESS--");
		return ;
	}
	if (strcmp(actual, expected))
	{
		printf("--FAIL--\nactual: %s\nexpected: %s\n", actual, expected);
		free(actual);
		return ;
	}
	free(actual);
	printf("%s\n", "--SUCCESS--");
}

void test_path_orchestrator(void)
{
	t_error err = 0;
	char *path = NULL;

	t_test_path pairs[] = {
		{NULL, NULL},
		{NULL, (char *[]){NULL}},
		{NULL, (char *[]){"", NULL}},
		{NULL, (char *[]){"HOME=abc", "VAR=def", NULL},},
		{NULL, (char *[]){"HOME=abc", "VAR=def", "PATH=/bin:/local/sbin:/homebrew/bin", NULL}},		
		{"", NULL},
		{"", (char *[]){NULL}},
		{"", (char *[]){"", NULL}},
		{"", (char *[]){"HOME=abc", "VAR=def", NULL},},
		{"", (char *[]){"HOME=abc", "VAR=def", "PATH=/bin:/local/sbin:/homebrew/bin", NULL}},		
		{"catt", NULL},
		{"catt", (char *[]){NULL}},
		{"catt", (char *[]){"", NULL}},
		{"catt", (char *[]){"HOME=abc", "VAR=def", NULL},},
		{"catt", (char *[]){"HOME=abc", "VAR=def", "PATH=/bin:/local/sbin:/homebrew/bin", NULL}},	
		{"cat", NULL},
		{"cat", (char *[]){NULL}},
		{"cat", (char *[]){"", NULL}},
		{"cat", (char *[]){"HOME=abc", "VAR=def", NULL},},
		{"cat", (char *[]){"HOME=abc", "VAR=def", "PATH=/bin:/local/sbin:/homebrew/bin", NULL}},
		{"/bin/cat", (char *[]){"HOME=abc", "VAR=def", "PATH=/bin:/local/sbin:/homebrew/bin", NULL}},
		{"/bins/cat", (char *[]){"HOME=abc", "VAR=def", "PATH=/bin:/local/sbin:/homebrew/bin", NULL}},
	};

	char *expected[] = {
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		(char *){"/bin/cat"},
		(char *){"/bin/cat"},
		NULL
	};

	int i = 0;
	while (i < 22)
	{
		path = path_orchestrator(pairs[i].cmd, pairs[i].path_tab, &err);
		helper_test_path_orchestrator(path, expected[i]);
		i++;
	}
}