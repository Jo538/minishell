/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benji <benji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:55:42 by admin             #+#    #+#             */
/*   Updated: 2026/04/15 15:33:14 by benji            ###   ########.fr       */
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

// STRUCT

typedef struct s_segment
{
    char				*value;
    int					quote_type;
    struct s_segment	*next;
} t_segment;

typedef struct s_token
{
	struct s_token	*before;
	int				type;
	t_segment		*segments;
	struct s_token	*next;
} t_token;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
} t_redir;

typedef struct s_tree
{
	int				type;
	char			**argv;
	t_redir			*redirections;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;

// FUNCT
char	*prompt_minishell(void);

#endif