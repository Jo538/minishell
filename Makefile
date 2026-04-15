# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: benji <benji@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/14 14:01:07 by admin             #+#    #+#              #
#    Updated: 2026/04/15 00:51:22 by benji            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror
ADDITIONAL_FLAGS = -lreadline
NAME = minishell

# Directories
INCLUDES = includes
SRC_DIR = src
OBJ_DIR = build
LIBFT_DIR = libft
TEST_DIR = tests

# Sources and Objects
SRC = main.c prompt.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LIBFT_ARCHIVE = $(LIBFT_DIR)/libft.a

# Default rule
all: $(NAME)

# Linking
$(NAME): $(OBJ) $(LIBFT_ARCHIVE)
	$(CC) $(OBJ) $(LIBFT_ARCHIVE) $(CFLAGS) $(ADDITIONAL_FLAGS) -o $(NAME)

# Object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) $(ADDITIONAL_FLAGS) -c $< -o $@

# Create libft archive
$(LIBFT_ARCHIVE):
	$(MAKE) -C $(LIBFT_DIR)

# Create object directory
$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

# Phony targets declaration
.PHONY: all clean fclean re

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