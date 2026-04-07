NAME        = minishell
CC            = cc
AR            = ar rcs
RM            = rm -f
CFLAGS        = -Wall -Wextra -Werror -lreadline

PATH_printf = LIBS/printf
PRINTF = LIBS/printf/libftprintf.a


SRC_MINISHELL = main.c \
				$(addprefix prompt_attente/, prompt.c)

all: $(NAME)

$(PRINTF) :
	@make -C $(PATH_printf)

SRC            = $(SRC_MINISHELL)

OBJ            = $(SRC:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(PRINTF) $(OBJ)
	$(CC) $(OBJ) $(PRINTF) $(CFLAGS) -o $(NAME)

clean:
	@make clean -C $(PATH_printf)
	$(RM) $(OBJ)

fclean: clean
	@make fclean -C $(PATH_printf)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re