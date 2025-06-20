NAME = webserv

SRC =   main.cpp \
  		MainSrc/ParceConf.cpp\
		MainSrc/Servers.cpp \
		MainSrc/Location.cpp \
		MainSrc/Multiplexing.cpp\
	  	MainSrc/Request.cpp\
	  	Methods/Get.cpp\
	  	Methods/Post.cpp\
	  	Methods/Method.cpp\
		Methods/Cgi.cpp\
		Methods/Delete.cpp\

CXX = c++

CXXFLAGS =  -Wall -Wextra -Werror -std=c++98 #-fsanitize=address -g3 

OBJ = ${SRC:.cpp=.o}

RM	= rm -rf

all : ${NAME}

${NAME} : ${OBJ}
		${CXX} ${CXXFLAGS} ${OBJ} -o ${NAME}

clean : 
		${RM} ${OBJ}

fclean : clean
		${RM} ${NAME}

re	: fclean all