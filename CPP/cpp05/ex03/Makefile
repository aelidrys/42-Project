NAME = ZIntern

CXX = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98

OBJ = main.o Bureaucrat.o AForm.o PresidentialPardonForm.o\
RobotomyRequestForm.o ShrubberyCreationForm.o Intern.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all