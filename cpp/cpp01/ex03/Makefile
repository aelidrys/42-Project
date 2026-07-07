NAME = Human

CPP = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

OBJ = main.o Weapon.o HumanA.o HumanB.o

all : $(NAME)

$(NAME) : $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

%.o:%.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all