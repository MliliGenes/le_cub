CC = cc 
CFILES = main.c parssing/file_check.c
NAME = cub3d
FLAGS = -Wall -Wextra -Werror
OFILES = $(CFILES:.c=.o)

all : $(NAME)

%.o : %.c includes/func.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OFILES)
	$(CC) $(FLAGS) $(OFILES) -o $(NAME)

clean :
	rm -rf $(OFILES)

fclean :
	rm -rf $(OFILES) $(NAME)

re : fclean all