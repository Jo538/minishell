/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:55:42 by admin             #+#    #+#             */
/*   Updated: 2026/05/26 02:51:42 by admin            ###   ########.fr       */
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
	ERR_FATAL = -1,
	NO_ERR = 0,
	ERR_CMD = 1,
	ERR_CMD_FILE = 2,
	ERR_FILE = 3,
	ERR_PERMISSION = 4,
	ERR_INVALID_IDENTIFIER = 5,
	ERR_NON_NUMERIC_ARGUMENT = 6,
	ERR_TOO_MANY_ARGS = 7,
	ERR_SYNTAX = 8
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

# define OPEN_FILE 1
# define OPEN_CMD 2

# define NODE_CMD 1
# define NODE_PIPE 2

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

typedef struct s_env 
{
	char	*key;
	char	*value;
	int		export_flag;
	int		set_flag;
}	t_env;

///CHECKER

int	check_ifgood(t_token *token);
int	check_redirs(t_token *token);

// env
t_env	**create_env(char **envp, int *exit_code);
void	free_my_env(t_env **my_env);
char	**consolidate_my_env(t_env **my_env, int *exit_code);

// FUNCT
void	free_and_exit(t_tree *node, t_env **my_env, int *exit_code);
t_state	create_current_state(char c, int i, t_state previous_state);
t_token	*create_token(t_state current_state, t_token *tail, int *exit_code);
int		check_new_token(int i, t_state previous_state, t_state current_state);
void	change_token_type(t_state current_state, t_token *last_token, int *exit_code);
t_segment	*segment_orchestrator(t_state previous_state, t_state current_state, t_segment *segment, int *exit_code);
void	free_token_list(t_token *token_list_head);
t_token	*lexer(char *prompt, int *exit_code);
char	*path_orchestrator(char *cmd, t_env **my_env, int *exit_code);
void	free_tab(char **tab);
void	cmd_orchestrator(t_tree *current_node, t_env **my_env, int *exit_code);
void	files_redirections_orchestrator(char *cmd, int *pipefd, t_redir *redir, int *exit_code);
void	pipe_orchestrator(t_tree *root, t_tree *node, t_env **my_env, int *exit_code);
void	child_process(int *pipefd, t_tree *node, t_env **my_env, int *exit_code);
int	inspect_child_status(pid_t child, int status);
void	executor(t_tree *node, t_env **my_env, int *exit_code);
void	errors(int *exit_code);
void	error_orchestrator(int *exit_code, int translate, int error, int type, char *cmd, char *file);
/// PARSING

t_token	*find_last_pipe(t_token *token);
t_token	*gt_pipe_left(t_token *tok);
t_tree	*create_pipe_in_tree(t_tree *tree, t_token *token_trot);
t_tree	*make_right_part(t_token *token);
t_tree	*put_right_part(t_tree *tree);
t_tree	*fill_right_part(t_tree *tree);
int		have_a_token_left(t_token *token);
t_token	*go_to_pipe_left(t_token *token);
t_tree	*put_pipe_in_tree(t_tree *tree, t_token *token);
t_tree	*create_pipe_part(t_token *token);
t_token	*find_last_pipe(t_token *token);
t_tree	*create_tree(t_token *token);
t_tree	*parsing_main(t_token *token);
t_tree	*handle_redirs_etc_parsing(t_tree *to_return, t_token *token);
t_token	*expand_tokens(t_token	*token);
t_tree	*handle_redirs_etc_parsing(t_tree *to_return, t_token *token);
int		have_pipe(t_token *token);
void	free_the_tree(t_tree *tree, t_token *token);
char	*join_segments(t_token *token);
t_tree	*init_tree_w_malloc(t_token *token);
t_tree	*fill_av(t_tree *tree);
t_tree	*handle_redirs(t_tree *tree);

// builtins
void	free_node(t_tree *node);
void	run_echo(char **cmd);
void	run_env(t_env **my_env);
void	run_exit(char **cmd, int *exit_code);
void	run_pwd(void);
int	is_builtin(t_tree *node);
void	builtin_orchestrator(t_tree *root, t_tree *node, t_env **my_env, int *exit_code);
void	run_cd(char **cmd, int *exit_code);
t_env	**run_export(char **cmd, t_env **my_env, int *exit_code);
void	append_value(char *cmd, t_env *row, int *exit_code);
void	append_key(char *cmd, t_env *row, int *exit_code);
t_env	**create_new_row(char *cmd, t_env **my_env, int *exit_code);
t_env	**run_unset(char **cmd, t_env ** my_env, int *exit_code);



#endif