NAME = Character

CXX = c++

CPPFLAGS = -Wall -Wextra -Werror

OBJ = main.o Character.o AMateria.o Cure.o Ice.o Box.o\
ICharacter.o IMateriaSource.o MateriaSource.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all