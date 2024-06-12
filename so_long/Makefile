OBJ = a_so_long.o touls.o split.o a_check_map1.o get_next_line.o\
get_next_line_utils.o a_check_map2.o a_imge_to_win.o a_imge_touls.o

BONUS_OBJ = b_so_long_bonus.o touls.o split.o b_check_map1_bonus.o get_next_line.o\
get_next_line_utils.o b_check_map2_bonus.o b_imge_to_win_bonus.o b_animation1_bonus.o\
b_imge_touls_bonus.o b_animation2_bonus.o

NAME = so_long

NAME_BONUS = so_long_bonus

CFLAGS = -Wall -Wextra -Werror

MLX_MFLAGS = -lmlx -framework OpenGL -framework AppKit
MLX_UFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(MLX_UFLAGS)

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(BONUS_OBJ)
	$(CC)  $(BONUS_OBJ) -o $(NAME_BONUS) $(MLX_UFLAGS)

clean :
	rm -f $(OBJ) $(BONUS_OBJ)

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: clean