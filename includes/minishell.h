/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:55:42 by admin             #+#    #+#             */
/*   Updated: 2026/04/19 13:30:46 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

// ENUM - ERRORS
typedef enum e_error
{
	ERR_MALLOC = 1,
}	t_error;

// ENUM - Lexer states
typedef enum e_quoting
{
	UNQUOTED = 1,
	S_QUOTED,
	D_QUOTED,
}	t_quoting;

typedef enum e_char_type
{
	ON_SPACE = 1,
	ON_OPERATOR,
	ON_WORD
}	t_char_type;

typedef enum e_token
{
	WORD = 1,
	PIPE,
	IN_DIR,
	OUT_DIR,
	HEREDOC,
	APPEND_OUT_DIR
}	t_token_type;

// STRUCT
typedef struct s_state
{
	char	c;
	int		quoting;
	int		char_type;
	int		repeat;
}	t_state;

typedef struct s_segment
{
	char				*value;
	t_quoting			quote_type;
	struct s_segment	*next;
}	t_segment;

typedef struct s_token
{
	struct s_token	*before;
	int				type;
	t_segment		*segments;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_tree
{
	int				type;
	char			**argv;
	t_redir			*redirections;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

// FUNCT
t_state	*create_current_state(char c, t_state *previous_state, t_error *err);

#endif