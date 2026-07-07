NAME = minishell

E_OBJ = e_srcs/main.o e_srcs/command.o  e_srcs/builtines.o e_srcs/toulse1.o\
e_srcs/unset.o e_srcs/cd.o e_srcs/echo.o  e_srcs/exit.o  e_srcs/split.o\
e_srcs/get_path.o e_srcs/environment.o e_srcs/export.o e_srcs/errors.o\
e_srcs/multible_cmd.o e_srcs/signals.o e_srcs/string_action.o

P_OBJ = p_srcs/main.o p_srcs/split_space_quoted.o p_srcs/expander.o\
p_srcs/handling.o p_srcs/ft_dup_envp.o p_srcs/fill_nodes.o p_srcs/ft_last_split.o\
p_srcs/help.o p_srcs/ft_split_command.o p_srcs/get_infile_outfile.o\
p_srcs/heredoc_handle.o p_srcs/parsing.o p_srcs/set_vars.o p_srcs/heredoc_gest.o\
p_srcs/help_to_fill.o p_srcs/get_heredoc_help.o p_srcs/ft_add_quotes.o p_srcs/help_expand.o\
p_srcs/get_in_help.o

CC = cc
CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address
RD_FLAGS = -I ~/Users/aelidrys/goinfre/homebrew/Cellar/readline/8.2.1/include  -L /Users/aelidrys/goinfre/homebrew/Cellar/readline/8.2.1/lib -lreadline



all : $(NAME)

$(NAME) : $(E_OBJ) $(P_OBJ)
	make -C libft/
	$(CC) $(CFLAGS) -L libft/ -lft $(P_OBJ) $(E_OBJ) -o $(NAME) $(RD_FLAGS)

build : $(OBJ)
	ar -rc lib.a $?

clean :
	rm -f $(E_OBJ)
	rm -f $(P_OBJ)

clean_all :
	rm -f $(E_OBJ)
	rm -f $(P_OBJ)
	make clean -C libft/

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean