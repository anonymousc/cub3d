NAME = Cub3D

CC = cc


CFLAGS = -Wextra -Wall -Werror  -I./include/
SRC = main.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Lminilibx-linux -lXext -lX11  -lmlx_Linux -lz -lm -o $(NAME)
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.SECONDARY : $(OBJ)
