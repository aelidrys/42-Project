NAME		= libft.a

SRCS	=		ft_memset.c		\
		  		ft_memchr.c		\
		  		ft_memmove.c	\
		  		ft_memcmp.c		\
		  		ft_memcpy.c		\
		  		ft_bzero.c		\
		  		ft_atoi.c		\
		  		ft_strlen.c		\
		  		ft_strlcpy.c	\
		 	 	ft_strchr.c		\
		 		ft_strrchr.c	\
		  		ft_strnstr.c	\
				ft_strnstr.c	\
				ft_strncmp.c	\
		  		ft_atoi.c		\
		  		ft_isalnum.c	\
				ft_strlcat.c	\
		  		ft_isdigit.c	\
		  		ft_isalpha.c	\
		  		ft_isascii.c	\
		 		ft_isprint.c	\
		  		ft_tolower.c	\
		  		ft_toupper.c	\
		  		ft_calloc.c		\
		  		ft_strdup.c		\
				ft_substr.c		\
				ft_strjoin.c	\
				 ft_split.c		\
				ft_itoa.c		\
				 ft_strtrim.c	\
				ft_putchar_fd.c	\
				ft_putstr_fd.c \
				ft_putendl_fd.c	\
				ft_putnbr_fd.c \
				ft_striteri.c \
				ft_strmapi.c \
				ft_strjoin_get.c\
				get_next_line.c \
				ft_strcmp.c\

OBJS	= ${SRCS:.c=.o}

RM		= rm -rf

CC		= cc

AR		= ar rc

CFLAGS = -Wall -Werror -Wextra

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(AR) $(NAME) $(OBJS)

clean	:	
		$(RM) ${OBJS}


fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
