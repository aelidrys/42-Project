OBJ = soLongBonus/main.o soLongBonus/touls.o soLongBonus/split.o soLongBonus/check_map1.o\
soLongBonus/get_next_line.o soLongBonus/get_next_line_utils.o soLongBonus/check_map2.o soLongBonus/imge_to_win.o\
soLongBonus/animation1.o soLongBonus/imge_touls.o soLongBonus/animation2.o


CC = gcc

NAME = so_long

CFLAGS = -Wall -Wextra -Werror

MLX_MFLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit

MLX_UFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

# FLAG = -fsanitize=address -g

all : $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@


$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(MLX_UFLAGS) -o $(NAME)


clean :
	rm -f $(OBJ) $(BONUS_OBJ)

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: clean