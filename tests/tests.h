/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:18:27 by admin             #+#    #+#             */
/*   Updated: 2026/05/04 20:48:17 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "minishell.h"
# include <glob.h>

extern int	tests_run;
extern int	tests_passed;

# define PASS 0
# define FAIL 1

typedef struct s_test_segment
{
    char *value;
    t_quoting quoting_type;
} t_test_segment;

typedef struct s_test_token
{
    t_token_type token_type;
    int count_segment;
    t_test_segment *segment;
} t_test_token;

typedef struct s_test_case
{
    int num_token;
    t_test_token *expected_tokens;
} t_test_case;

typedef struct s_test_path
{
    char *cmd;
    char **path_tab;
} t_test_path;

# define TEST_ASSERT(actual, expected, msg) do {        \
      tests_run++;                                \
      if (actual == expected) {                            \
          printf("PASS: %s\n", msg);             \
          tests_passed++;                         \
      } else {                                    \
          printf("FAIL: %s (line %d)\n", msg, __LINE__); \
          printf("Actual: %d\n", actual);          \
          printf("Expected: %d\n", expected);        \
      }                                           \
  } while(0)

void test_create_current_state(void);
void test_find_token_type(void);
void test_check_new_token(void);
void test_create_token(void);
void test_add_new_segment(void);
void test_append_to_segment(void);
void test_change_token_type(void);
void test_free_token_list(void);
void	test_lexer_orchestrator(void);
void	test_extract_paths(void);
void test_find_and_check_path(void);
void test_path_orchestrator(void);
// void	test_parent_orchestrator(void);
// void test_pipe_orchestrator(void);
// void test_orchestrator(void);
void test_improved_version_executor(void);

// Static functions
t_token_type	find_token_type(t_state current_state);
t_segment	*add_new_segment(t_state current_state, t_segment *last_segment, t_error *err);
void	append_to_segment(t_state current_state, t_segment *last_segment, t_error *err);
char	**extract_paths(char *cmd, char **env, t_error_exec *err);
char	*find_and_check_path(char *cmd, char **path_tab, t_error_exec *err);
#endif