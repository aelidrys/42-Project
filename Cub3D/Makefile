NAME = cub3D

NAME_BONUS = cub3D_bonus

SRC =	src/cub3D.c\
		src/main.c\
		src/cub3D_parce.c\
		src/free_err.c\
		src/cub_tool1.c\
		src/moves.c\
		src/functions_mlx.c\
		src/linked.c\
		src/string_action.c\
		src/parce_first_element.c\
		src/drawing.c\
		src/det_coord.c\
		src/drawing_walls.c\
		src/cub_utils.c\
		src/cub.c\

SRC_BONUS =	src_bonus/cub3D_bonus.c\
		src_bonus/main_bonus.c\
		src_bonus/cub3D_parce_bonus.c\
		src_bonus/free_err_bonus.c\
		src_bonus/cub_tool1_bonus.c\
		src_bonus/mini_map_bonus.c\
		src_bonus/moves_bonus.c\
		src_bonus/functions_mlx_bonus.c\
		src_bonus/linked_bonus.c\
		src_bonus/wapean_bonus.c\
		src_bonus/string_action_bonus.c\
		src_bonus/parce_first_element_bonus.c\
		src_bonus/drawing_bonus.c\
		src_bonus/det_coord_bonus.c\
		src_bonus/drawing_walls_bonus.c\
		src_bonus/open_door_bonus.c\
		src_bonus/cub_utils_bonus.c\
		src_bonus/cub_bonus.c\

OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}


CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g

MLX_FLAG = -lmlx -framework OpenGL -framework AppKit

RM = rm -rf

CC = cc

all : ${NAME}

${NAME} : ${OBJ}
		make -C libft
		${CC} ${CFLAGS} ${OBJ} libft/libft.a -o ${NAME} $(MLX_FLAG)

bonus	: ${NAME_BONUS}

${NAME_BONUS} : ${OBJ_BONUS}
		make -C libft
		${CC} ${CFLAGS} ${OBJ_BONUS} libft/libft.a -o ${NAME_BONUS} $(MLX_FLAG)

clean :
	$(RM) $(OBJ)
	$(RM) $(OBJ_BONUS)

clean_all :
	make clean -C libft
	$(RM) $(OBJ)
	$(RM) $(OBJ_BONUS)

fclean	:	clean
		make fclean -C libft
		$(RM) $(NAME)
		$(RM) $(NAME_BONUS)

re	:	fclean all bonus