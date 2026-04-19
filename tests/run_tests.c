/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:17:56 by admin             #+#    #+#             */
/*   Updated: 2026/04/19 13:31:42 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	tests_run;
int	tests_passed;

int	main(void)
{
	printf("%s", "--------------CREATION OF CURRENT STATE BASED ON PREVIOUS STATE AND CHAR--------------\n\n");
	test_create_current_state();
}
