/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:17:56 by admin             #+#    #+#             */
/*   Updated: 2026/04/20 15:32:58 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	tests_run;
int	tests_passed;

int	main(void)
{
	printf("%s", "--------------CREATION OF CURRENT STATE BASED ON PREVIOUS STATE AND CHAR--------------\n\n");
	test_create_current_state();
	printf("%s", "--------------CORRECT TOKEN TYPE IDENTIFIED--------------\n\n");
	test_find_token_type();
	printf("%s", "--------------CREATE NEW TOKEN OR APPEND TO TOKEN OR APPEND AND CHANGE TOEKN TYPE--------------\n\n");
	test_check_new_token();
}
