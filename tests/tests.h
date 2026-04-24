/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:18:27 by admin             #+#    #+#             */
/*   Updated: 2026/04/24 22:52:30 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "minishell.h"

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

// Static functions
t_token_type	find_token_type(t_state current_state);
t_segment	*add_new_segment(t_state current_state, t_segment *last_segment, t_error *err);
void	append_to_segment(t_state current_state, t_segment *last_segment, t_error *err);
void	test_lexer_orchestrator(void);

#endif