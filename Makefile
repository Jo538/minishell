# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: benji <benji@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/14 14:01:07 by admin             #+#    #+#              #
#    Updated: 2026/05/06 15:56:55 by benji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler
CC = cc
CFLAGS = -g3 -O0
VPATH = src:src/lexer:src/parsing:src/executor
ADDITIONAL_FLAGS = -lreadline # to remove the macos part when pushing to main
NAME = minishell
TEST_NAME = test_minishell
ADDITIONAL_FLAGS = -lreadline
INCLUDES = -Iincludes -Ilibft
LIBFT_DIR = libft
OBJ_DIR = obj

# Sources and Objects
SRC = main.c signals.c create_state.c create_token.c append_to_token.c \
	orchestrator.c path.c child.c redirections.c pipe.c exec_orchestrator.c \
	parsing.c parsing_utils.c parsing_right_part.c \
	parsing_pipes.c parsing_expand.c parsing_redirs.c
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