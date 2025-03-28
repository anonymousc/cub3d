NAME = cub3D

CC = cc


CFLAGS = -I./include/ -O3 -g3  -Wextra -Wall -Werror -fsanitize=address
SRC = main.c $(wildcard raycasting/*.c) $(wildcard parsing/map_validation/*.c) $(wildcard parsing/map_validation/texture_parsing/*.c)  $(wildcard parsing/map_validation/color_parsing/*.c)  $(wildcard parsing/map_validation/map_parsing/*.c) $(wildcard parsing/parsing_utils/*.c)

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lbsd -lm -lmlx -lz -o $(NAME)
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

re : fclean all

run : re
	./Cub3D map/test.cub

.SECONDARY : $(OBJ)