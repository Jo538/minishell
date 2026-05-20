/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:17:56 by admin             #+#    #+#             */
/*   Updated: 2026/05/20 01:38:00 by admin            ###   ########.fr       */
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
	printf("%s", "--------------TOKEN CREATION ORCHESTRATOR WORKING--------------\n\n");
	test_create_token();
	printf("%s", "--------------ADD NEW SEGMENT TO LIST OF SEGMENTS--------------\n\n");
	test_add_new_segment();
	// printf("%s", "--------------APPEND VALUE TO EXISTING SEGMENT--------------\n\n");
	// test_append_to_segment();
	// printf("%s", "--------------CHANGE TOKEN TYPE TO HEREDOC OR APPEND_OUT_DIR--------------\n\n");
	// test_change_token_type();
	printf("%s", "--------------TEST IF FREE_ALL WORKS--------------\n\n");
	test_free_token_list();
	printf("%s", "--------------TEST ENTIRE LEXER ORCHESTRATOR--------------\n\n");	
	test_lexer_orchestrator();
	printf("%s", "--------------TEST PATH EXTRACTION EXECUTION--------------\n\n");	
	test_extract_paths();
	printf("%s", "--------------TEST PATH EXTRACTION EXECUTION--------------\n\n");	
	test_find_and_check_path();
	printf("%s", "--------------TEST PATH ORCHESTRATOR-------------\n\n");	
	test_path_orchestrator();
	printf("%s", "--------------TEST CMD ORCHESTRATOR-------------\n\n");	
	// printf("%s", "--------------TEST EXECUTOR-------------\n\n");	
	// test_improved_version_executor();
	printf("%s", "--------------TEST CD BUILTIN-------------\n\n");	
	test_cd();
	printf("%s", "--------------TEST ENV-------------\n\n");	
	test_env();
	printf("%s", "--------------TEST CONSOLIDATION ENV-------------\n\n");	
	test_consolidate_env();
	printf("%s", "--------------TEST EXPORT BUILTIN-------------\n\n");	
	test_export();
}
