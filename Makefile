CC = cc 
CFILES = main.c parssing/file_check.c parssing/gnl.c parssing/gnl_utils.c \
parssing/parse_map.c parssing/split.c parssing/utils.c
NAME = cub3d
#FLAGS = -Wall -Wextra -Werror
OFILES = $(CFILES:.c=.o)

all : $(NAME)

%.o : %.c includes/func.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OFILES)
	$(CC) $(FLAGS) $(OFILES) -o $(NAME) -fsanitize=address

clean :
	rm -rf $(OFILES)

fclean :
	rm -rf $(OFILES) $(NAME)

re : fclean all