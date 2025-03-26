NAME = Cub3D

CC = cc


CFLAGS = -I./include/ -O3 -fsanitize=address -g3 #-Wextra -Wall -Werror 
SRC = main.c raycasting/cub_init.c raycasting/rgb.c raycasting/intersections_alg.c raycasting/algo_helpers.c parsing/map_validation/map_validation_core.c  parsing/map_validation/textures_core.c  parsing/map_validation/colors_core.c parsing/file_validation.c parsing/map_validation/map_core.c $(wildcard parsing/parsing_utils/*.c)

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