/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:18:27 by admin             #+#    #+#             */
/*   Updated: 2026/04/15 18:20:08 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "minishell.h"

extern int	tests_run;
extern int	tests_passed;

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


#endif