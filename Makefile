# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admin <admin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/14 14:01:07 by admin             #+#    #+#              #
#    Updated: 2026/04/15 23:24:16 by admin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc
CFLAGS = 
ADDITIONAL_FLAGS = -L/opt/homebrew/opt/readline/lib -lreadline # to remove the macos part when pushing to main
NAME = minishell
TEST_NAME = test_minishell

# Directories
INCLUDES = -Iincludes -Ilibft -I/opt/homebrew/opt/readline/include # to remove the macos part when pushing to main
SRC_DIR = src
OBJ_DIR = build
TEST_DIR = tests
LIBFT_DIR = libft

# Sources and Objects
SRC = main.c prompt.c
TEST_SRC = $(addprefix $(TEST_DIR)/, $(SRC:.c=.o))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
TEST_OBJ = $(addprefix $(OBJ_DIR)/, $(TEST_SRC:.c=.o))
LIBFT_ARCHIVE = $(LIBFT_DIR)/libft.a

# Default rule
all: $(NAME)

# Linking
$(NAME): $(OBJ) $(LIBFT_ARCHIVE)
	$(CC) $(OBJ) $(LIBFT_ARCHIVE) $(CFLAGS) $(ADDITIONAL_FLAGS) -o $(NAME)

# Object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create libft archive
$(LIBFT_ARCHIVE):
	$(MAKE) -C $(LIBFT_DIR)

# Create object directory
$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

# Phony targets declaration
.PHONY: all clean fclean re test

# Clean project's object files
clean:
	@rm -f $(OBJ)
	@if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi

# Clean minishell executable and clean libraries
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

# Recompile all files
re: fclean
	$(MAKE) all

# Create test binary
test: $(TEST_OBJ) $(OBJ)
	$(CC) $(TEST_OBJ) $(filter-out $(OBJ_DIR)/main.o, ) $(LIBFT_ARCHIVE) $(CFLAGS) $(ADDITIONAL_FLAGS) -o $(TEST_NAME)
