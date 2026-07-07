NAME = Brains

CXX = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

OBJ = main.o Animal.o Cat.o Dog.o Brain.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all