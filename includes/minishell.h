/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:55:42 by admin             #+#    #+#             */
/*   Updated: 2026/05/06 15:38:21 by benji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
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

// ENUMS

typedef enum e_cmd_type
{
	LITERAL,
	PATH
}	t_cmd_type;

typedef enum e_state
{
	PREVIOUS_STATE,
	CURRENT_STATE
}	t_enum_state;

typedef enum e_quoting
{
	UNQUOTED = 1,
	S_QUOTED,
	D_QUOTED
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
	APPEND_OUT_DIR,
	CMD
}	t_token_type;

// STRUCTS that live throughout project

# define OPEN_OPE 1
# define CMD_OPE 2

# define NODE_CMD 1
# define NODE_PIPE 2

typedef struct	s_error_exec
{
	int		err;
	int		operation;
	char	*cmd;
}	t_error_exec;

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
	t_token			*token_ref;
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
char	*path_orchestrator(char *cmd, char **env, t_error_exec *err);
void	free_tab(char **tab);
int	cmd_orchestrator(t_tree *current_node, char **env, t_error_exec *err);
void	files_redirections_orchestrator(int *pipefd, t_redir *redir, t_error_exec *err);
int	pipe_orchestrator(t_tree *node, char **env, t_error_exec *err);
void	child_process(int *pipefd, t_tree *node, char **env, t_error_exec *err);
int	inspect_child_status(pid_t child, int status);
int	execute(t_tree *node, char **env);
void	errors(int *pipefd, t_error_exec *err);

/// PARSING

t_token	*find_last_pipe(t_token *token);
t_token	*gt_pipe_left(t_token *tok);
t_tree	*create_pipe_in_tree(t_tree *tree, t_token *token_trot);
t_tree	*make_right_part(t_token *token, t_tree *tree);
t_tree	*put_right_part(t_tree *tree);
t_tree	*fill_right_part(t_tree *tree);
t_tree	*put_pipe_in_tree(t_tree *tree, t_token *token);
t_tree	*create_pipe_part(t_token *token);
t_token	*find_last_pipe(t_token *token);
t_tree	*create_tree(t_token *token);
int		have_a_token_left(t_token *token);
t_token	*go_to_pipe_left(t_token *token);
int		get_size_of_tokens(t_token *token);
t_tree	*parsing_main(t_token *token);
t_tree	*handle_redirs_etc_parsing(t_tree *to_return, t_token *token);
t_token	*expand_tokens(t_token	*token);


#endif