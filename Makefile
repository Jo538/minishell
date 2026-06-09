# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admin <admin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/14 14:01:07 by admin             #+#    #+#              #
#    Updated: 2026/06/09 12:30:49 by admin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O0
VPATH = src:src/lexer:src/check_if_good:src/executor:src/parsing:src/executor/builtins:src/env:tests
NAME = minishell
TEST_NAME = test_minishell
ifeq ($(shell uname), Darwin)
	ADDITIONAL_FLAGS = -L/opt/homebrew/opt/readline/lib -lreadline
else
	ADDITIONAL_FLAGS = -lreadline
endif

# Directories
ifeq ($(shell uname), Darwin)
	INCLUDES = -Iincludes -Ilibft -I/opt/homebrew/opt/readline/include
else
	INCLUDES = -Iincludes -Ilibft
endif
LIBFT_DIR = libft
OBJ_DIR = obj

# Sources and Objects
SRC = main.c signals.c create_state.c create_token.c append_to_token.c \
	orchestrator.c path.c child.c redirections.c heredoc.c pipe.c \
	exec_orchestrator.c errors.c free_node.c \
	parsing.c parsing_utils.c parsing_right_part.c \
	parsing_pipes.c parsing_expand.c parsing_redirs.c parsing_free.c \
	make_right_part_utils.c right_part_utils_redirs.c \
	check_redirs.c check_ifgood.c exit.c pwd.c echo.c cd.c create_env.c \
	consolidate_env.c env.c export.c export_print.c export_utils.c unset.c \
	builtin_orchestrator.c
TEST_SRC = run_tests.c test_lexer.c test_create_token.c test_append_to_token.c \
	test_orchestrator.c test_path.c test_child.c test_builtins.c test_env.c
	
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
.PHONY: all clean fclean re test 

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

test: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=file.supp ./minishell
