# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 11:15:08 by jchartie          #+#    #+#              #
#    Updated: 2025/11/24 16:02:39 by jchartie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
MAIN_SOURCES = ft_calloc.c	ft_isascii.c	ft_itoa.c	ft_memcpy.c	\
ft_putchar_fd.c	ft_putstr_fd.c	ft_strdup.c	ft_strlcat.c	ft_strmapi.c	\
ft_strrchr.c	ft_tolower.c	ft_atoi.c	ft_isalnum.c	ft_isdigit.c	\
ft_memchr.c	ft_memmove.c	ft_putendl_fd.c	ft_split.c	ft_striteri.c	\
ft_strlcpy.c	ft_strncmp.c	ft_strtrim.c	ft_toupper.c	\
ft_bzero.c	ft_isalpha.c	ft_isprint.c	ft_memcmp.c	ft_memset.c	\
ft_putnbr_fd.c	ft_strchr.c	ft_strjoin.c	ft_strlen.c	ft_strnstr.c	\
ft_substr.c
BONUS_SOURCES = ft_lstnew_bonus.c	ft_lstadd_front_bonus.c	\
ft_lstsize_bonus.c	ft_lstlast_bonus.c	ft_lstadd_back_bonus.c	\
ft_lstdelone_bonus.c	ft_lstclear_bonus.c	ft_lstiter_bonus.c	\
ft_lstmap_bonus.c
MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)
BONUS_OBJECTS = $(BONUS_SOURCES:.c=.o)
NAME = libft.a

# Default rule
all: $(NAME)

# Compilation of the main file wihout bonuses
$(NAME): $(MAIN_OBJECTS)
	ar rcs $(NAME) $(MAIN_OBJECTS)

# Compilation of the .c files into .o files (main + bonus)
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) 

# Phony targets declaration
.PHONY: all clean fclean re bonus

# Compilation of bonus .c files into .o files
bonus: $(BONUS_OBJECTS) $(NAME) 
	ar rcs $(NAME) $(BONUS_OBJECTS)

# Removal of object files
clean:
	rm -f $(MAIN_OBJECTS) $(BONUS_OBJECTS)

# Removal of compiled file
fclean: clean
	rm -f $(NAME)

# Recompile all files
re: fclean all

