NAME = philo

OBJ = philosophers.o toulse1.o toulse2.o toulse3.o\

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