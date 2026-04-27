/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:55:42 by admin             #+#    #+#             */
/*   Updated: 2026/04/26 16:21:16 by admin            ###   ########.fr       */
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

// ENUMS - ERRORS
typedef enum e_error
{
	ERR_MALLOC = 1,
}	t_error;

// ENUMS - Lexer
typedef enum e_state
{
	PREVIOUS_STATE,
	CURRENT_STATE,
}	t_enum_state;

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

// STRUCTS that live throughout project
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
	t_segment		*segment;
	struct s_token	*next;
}	t_token;

typedef struct s_key_items
{
	t_token		*first_token;
	t_token		*last_token;
	t_segment	*last_segment;
}	t_key_items;

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
t_state	create_current_state(char c, int i, t_state previous_state);
t_token	*create_token(t_state current_state, t_token *tail, t_error *err);
int		check_new_token(int i, t_state previous_state, t_state current_state);
void	change_token_type(t_state current_state, t_token *last_token, t_error *err);
t_segment	*segment_orchestrator(t_state previous_state, t_state current_state, t_segment *segment, t_error *err);
void	free_token_list(t_token *token_list_head);
t_token	*lexer_orchestrator(char *prompt, t_error *err);

#endif