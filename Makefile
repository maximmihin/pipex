NAME = pipex

HEADER = includes/pipex.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC = libft_func/ft_split.c libft_func/ft_strjoin.c libft_func/ft_strlen.c \
		libft_func/ft_strncmp.c libft_func/ft_substr.c \
		src/childs.c src/pipex.c

OBJ = $(SRC:%.c= %.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o	: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean	:
	@rm -f $(OBJ)

fclean	:	clean
	@$(RM) $(NAME)

re	:	fclean all