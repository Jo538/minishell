# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bribot <bribot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/14 14:01:07 by admin             #+#    #+#              #
#    Updated: 2026/06/10 17:20:22 by bribot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O0
VPATH = src:src/lexer:src/check_if_good:src/executor:src/parsing:src/executor/builtins:src/env:tests
NAME = minishell
TEST_NAME = test_minishell
ADDITIONAL_FLAGS = -lreadline

# Directories
INCLUDES = -Iincludes -Ilibft

LIBFT_DIR = libft
OBJ_DIR = obj

# Sources and Objects
SRC = main.c signals.c create_state.c create_token.c append_to_token.c \
	orchestrator.c path.c child.c redirections.c heredoc.c pipe.c \
	exec_orchestrator.c errors.c free_node.c \
	parsing.c parsing_utils.c parsing_right_part.c \
	parsing_pipes.c parsing_expand.c parsing_expand_utils.c parsing_redirs.c parsing_free.c \
	make_right_part_utils.c right_part_utils_redirs.c make_right_part_utilsbis.c parsing_pipes_utils.c\
	check_redirs.c check_ifgood.c exit.c pwd.c echo.c cd.c create_env.c \
	consolidate_env.c env.c export.c export_print.c export_utils.c unset.c \
	builtin_orchestrator.c
	
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LIBFT_ARCHIVE = $(LIBFT_DIR)/libft.a

# Default rule
all: $(NAME)

# Linking
$(NAME): $(OBJ) $(LIBFT_ARCHIVE)
	$(CC) $(OBJ) $(LIBFT_ARCHIVE) $(CFLAGS) $(ADDITIONAL_FLAGS) -o $(NAME)

# Object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create libft archive
$(LIBFT_ARCHIVE):
	$(MAKE) -C $(LIBFT_DIR)

# Phony targets declaration
.PHONY: all clean fclean re

# Clean project's object files
clean:
	@rm -rf $(OBJ_DIR)

# Clean minishell executable and clean libraries
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

# Recompile all files
re: fclean
	$(MAKE) all
