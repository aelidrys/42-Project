NAME = philo_bonus

OBJ = philosopher_bonus.o toulse1_bonus.o toulse2_bonus.o toulse3_bonus.o\

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean