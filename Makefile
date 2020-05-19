NAME = lem-in

LIBFT_DIR = ./libft/
LIBFT = lft
PRINTF_DIR = ./libft/ft_printf/
PRINTF = lftprintf
LIBFTPRINTF = ./libft/ft_printf/libftprintf.a
LIBFTLIB = ./libft/libft.a

INCL_DIR = ./includes/
INCL_H = lem_in.h lem_in_struct.h
INCL = $(addprefix $(INCL_DIR),$(INCL_H))

SRC_DIR = src/
SRC_C = lem_atoi.c lem_in_bfs.c lem_in_bfs_2.c lem_in_bfs_3.c\
		lem_in_bfs_expand.c lem_split.c main.c move_ants_1.c\
		lem_in_bfs_expand_2.c lem_in_bfs_expand_3.c\
		lem_in_bfs_expand_4.c lem_in_bfs_expand_5.c\
		lem_in_bfs_expand_6.c memory_deleter.c\
		error_management.c move_ants_2.c\
		parsing_1.c parsing_2.c	parsing_3.c parsing_4.c\

SRC = $(addprefix $(SRC_DIR),$(SRC_C))
SRC_O = $(SRC:%.c=%.o)

FLAGS =	-Wall -Werror -Wextra

all: $(LIBFT_DIR)$(LIBFT) $(NAME)

$(LIBFT_DIR)$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(SRC) $(INCL) $(LIBFTLIB) $(LIBFTPRINTF)
	gcc $(FLAGS) $(SRC) -I$(INCL_DIR) -L$(LIBFT_DIR) -$(LIBFT) -L$(PRINTF_DIR) -$(PRINTF) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(SRC_O)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean flcean re
