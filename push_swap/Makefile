NAME = push_swap

NAME_BONUS = checker

OBJ = a_push_swap.o a_check_arg.o a_get_arg.o a_touls1.o a_touls2.o a_instructions1.o\
a_instructions2.o a_touls3.o a_touls4.o

OBJ_BONUS = b_push_swap_bonus.o b_get_next_line_bonus.o b_touls1_bonus.o\
b_touls2_bonus.o b_touls3_bonus.o b_touls4_bonus.o b_instructions1_bonus.o\
b_instructions2_bonus.o

CC = cc

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

bonus : $(NAME_BONUS)

$(NAME_BONUS) : $(OBJ_BONUS)
	@$(CC) $(OBJ_BONUS) $(CFLAGS) -o $(NAME_BONUS)

clean :
	@rm -f $(OBJ) $(OBJ_BONUS)

fclean : clean
	@rm -f $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY : clean