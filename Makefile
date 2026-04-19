# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: admin <admin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/14 14:01:07 by admin             #+#    #+#              #
#    Updated: 2026/04/19 22:40:44 by admin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc
CFLAGS = -g3 -O0
VPATH = src:src/lexer:src/executor:tests
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
SRC = main.c signals.c lexer.c token.c
TEST_SRC = run_tests.c test_lexer.c
OBJ = $(SRC:.c=.o)
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

# Create test binary
test: $(TEST_SRC) $(SRC) $(LIBFT_ARCHIVE)
	$(CC)  -DTESTING  $(INCLUDES) $(filter-out src/main.c, $^) $(CFLAGS) $(ADDITIONAL_FLAGS) -o $(TEST_NAME)
	./test_minishell
