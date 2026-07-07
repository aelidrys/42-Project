NAME		=	libft.a

SRCS		=	ft_isalpha.c	ft_isdigit.c		ft_isalnum.c	\
				ft_isascii.c	ft_isprint.c		ft_strlen.c		\
				ft_strlcpy.c	ft_strlcat.c		ft_toupper.c	\
				ft_tolower.c	ft_strchr.c			ft_strrchr.c	\
				ft_strncmp.c	ft_strnstr.c		ft_atoi.c		\
				ft_memset.c		ft_bzero.c			ft_memcpy.c		\
				ft_memmove.c	ft_memchr.c			ft_memcmp.c		\
				ft_calloc.c		ft_strdup.c			ft_substr.c		\
				ft_strjoin.c	ft_strtrim.c		ft_split.c		\
				ft_itoa.c		ft_strmapi.c		ft_striteri.c	\
				ft_putchar_fd.c	ft_putstr_fd.c		ft_putendl_fd.c	\
				ft_putnbr_fd.c	ft_puthex_fd.c		ft_putptr_fd.c	\
				ft_uitoa.c		ft_nblen.c			ft_putset.c		\
				ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c	\
				ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c	\
				ft_lstclear.c	ft_lstiter.c		ft_lstmap.c		\
				ft_putlong_fd.c	ft_nullstrjoin.c	get_next_line.c \
				ft_abs.c		ft_printf.c			ft_printchar.c	\
				ft_printstr.c	ft_printnbr.c		ft_printhex.c	\
				ft_printptr.c	ft_printunbr.c		ft_parse.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror
CC		=	cc
RM		=	rm -rf

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
