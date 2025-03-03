NAME = Cub3D

CC = cc


CFLAGS = -Wextra -Wall -Werror  -I./include/ -g3 -fsanitize=address -g3 #-Lminilibx-linux -lmlx_Linux -lX11 -lXext -lbsd -lm  -lmlx -lz
SRC = main_copy.c parsing/map_validation.c parsing/file_validation.c $(wildcard parsing/parsing_utils/*.c)  #intersections_alg.c 

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o $(NAME)
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.SECONDARY : $(OBJ)
