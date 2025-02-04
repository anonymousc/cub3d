NAME = Cub3D

CC = cc


CFLAGS = -Wextra -Wall -Werror 
SRC = main_copy.c intersections_alg.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lbsd -lm -I./include/ -lmlx -lz -o $(NAME)
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.SECONDARY : $(OBJ)
