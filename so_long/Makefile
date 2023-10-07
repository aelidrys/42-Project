OBJ = a_so_long.o touls.o split.o a_check_map1.o get_next_line.o\
get_next_line_utils.o a_check_map2.o a_imge_to_win.o a_imge_touls.o

BONUS_OBJ = b_so_long_bonus.o touls.o split.o b_check_map1_bonus.o get_next_line.o\
get_next_line_utils.o b_check_map2_bonus.o b_imge_to_win_bonus.o b_animation1_bonus.o\
b_imge_touls_bonus.o b_animation2_bonus.o

NAME = so_long

NAME_BONUS = so_long_bonus

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(MLX_FLAGS) $(OBJ) -o $(NAME)

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(BONUS_OBJ)
	$(CC) $(MLX_FLAGS) $(BONUS_OBJ) -o $(NAME_BONUS)

clean :
	rm -f $(OBJ) $(BONUS_OBJ)

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: clean