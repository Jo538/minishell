/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 21:11:31 by admin             #+#    #+#             */
/*   Updated: 2026/05/23 05:18:32 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "tests.h"

// // array of char *
// // char *array[] --> char **array

// static void env_helper(t_env *my_env, char *exp_key, char *exp_value, int exp_exported_flag, int exp_set_flag)
// {
// 	if (strcmp(my_env->key, exp_key))
// 	{
// 		printf("--FAIL--\nExpected: %s\nActual: %s\n", exp_key, my_env->key); // --FAIL--\nexpected: X\nactual: X\n
// 		return ;
// 	}
// 	if (strcmp(my_env->value, exp_value))
// 	{
// 		printf("--FAIL--\nExpected: %s\nActual: %s\n", exp_value, my_env->value);
// 		return ;		
// 	}
// 	if (my_env->export_flag != exp_exported_flag)
// 	{
// 		printf("--FAIL--\nExpected: %d\nActual: %d\n", exp_exported_flag, my_env->export_flag);
// 		return ;		
// 	}
// 	if (my_env->set_flag != exp_set_flag)
// 	{
// 		printf("--FAIL--\nExpected: %d\nActual: %d\n", exp_set_flag, my_env->set_flag);
// 		return ;
// 	}
// 	printf("%s\n", "--SUCCESS--");
// }
// void	test_env(void)
// {
// 	char *envp[] = {"PATH=abc", "PWD=def", NULL};
// 	t_error err = 0;
// 	int i = 0;
// 	t_env **my_env = env_orchestrator(envp, &err);
// 	env_helper(my_env[0], "PATH", "abc", 1, 1);
// 	env_helper(my_env[1], "PWD", "def", 1, 1);
// 	free_my_env(my_env);
// }

// // array of pointers to struct
// // t_env *my_env[] decays to t_env **my_env
// void test_consolidate_env(void)
// {
// 	t_error err = 0;
// 	t_env *my_env[] = {&(t_env){"PATH", "/usr/admin", 1, 1}, &(t_env){"PWD", "/usr/admin/jo", 1, 1}, NULL};
// 	char **new_env = consolidate_my_env(my_env, &err);
// 	if (strcmp(new_env[0], "PATH=/usr/admin"))
// 		printf("--FAIL--\nExpected: %s\nActual: %s\n", "PATH=/usr/admin", new_env[0]);
// 	if (strcmp(new_env[1], "PWD=/usr/admin/jo"))
// 		printf("--FAIL--\nExpected: %s\nActual: %s\n", "PWD=/usr/admin/jo", new_env[1]);
// 	printf("%s\n", "--SUCCESS--");
// 	free_tab(new_env);
// }