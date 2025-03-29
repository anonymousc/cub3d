/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wolf3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:56:33 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/29 03:05:19 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 3
# define TEXTURE_SIZE 4
# if TEXTURE_SIZE > 4
#  undef TEXTURE_SIZE
#  define TEXTURE_SIZE 4
# endif
# define COLOR_SIZE 3
# if COLOR_SIZE > 3
#  undef COLOR_SIZE
#  define COLOR_SIZE 3
# endif
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define TURN_RIGHT 65363
# define TURN_LEFT 65361
# define TILE_SIZE 64
# define PI 3.14159265358979323846
# define TILE_SIZE 64
# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900
# define FOV 60
# define NUM_OF_RAYS WINDOW_WIDTH
# define STRIP_WIDTH 1

typedef struct s_tex
{
	int				iteration_level;
	char			*direction;
	char			*filename;
}					t_tex;

typedef struct s_color
{
	char			*surface;
	int				*rgb;
}					t_color;

typedef struct s_map
{
	double			x;
	double			y;
	double			n;
	int				x_len;
	int				y_len;
	int				**map;
}					t_map;

typedef struct s_parsing
{
	t_tex			*textures;
	t_color			*coloring;
	t_map			*map;
}					t_parsing;

typedef struct s_texture
{
	unsigned int	*north_texture;
	unsigned int	*south_texture;
	unsigned int	*east_texture;
	unsigned int	*west_texture;
	void			*north_img;
	void			*south_img;
	void			*east_img;
	void			*west_img;
	void			*north_addr;
	void			*south_addr;
	void			*east_addr;
	void			*west_addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_texture;

typedef struct s_player
{
	double			px;
	double			py;
	int				player_size;
	double			pangle;
	double			turn_direction;
	double			walk_direction;
	double			sidewalk;
	double			move_speed;
	double			rotation_speed;
}					t_player;

typedef struct s_rays
{
	double			ray_angle;
	bool			rayfacingup;
	bool			rayfacingdown;
	bool			rayfacingright;
	bool			rayfacingleft;
	double			horwallhitx;
	double			horwallhity;
	double			vertwallhitx;
	double			vertwallhity;
	bool			foundhorwallhit;
	bool			foundvertwallhit;
	bool			washitvertical;
	double			horzdistance;
	double			vertdistance;
	double			wallhitx;
	double			wallhity;
	double			distance;
	double			wallstripheight;
	double			xstep;
	double			ystep;
}					t_rays;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_player		*player;
	t_rays			*rays;
	t_texture		*texture;
	t_parsing		*parsing;
}					t_data;

int					getnlcount_check(char **str);
int					getnlcount1(char **str);
void				fill_color_buffers(t_data *data);
int					keyrelease(int keycode, void *data);
int					update(t_data *data);
void				f(t_data *data);
void				clear_window(t_data *data);
int					c(void *data);
int					keypress(int keycode, void *data);
void				render3dwalls(t_data *data, int i);
int					wallcolor(t_data *data, int i, int textureoffsetx,
						int textureoffsety);
void				fill_bg(t_data *data);
char				*get_texture(t_data *data, char *direction);
void				init_textures(t_data *data);
double				normalize_angle(double angle);
int					horz_interception(t_data *data, int i);
void				process_hor_interception(t_data *data, int i,
						double nexthortouchx, double nexthortouchy);
int					vert_interception(t_data *data, int i);
void				process_vert_interception(t_data *data, int i,
						double nextverttouchx, double nextverttouchy);
void				hor_ver_distances(t_data *data, int i);
void				render3dwalls(t_data *data, int i);
bool				collision(double x, double y, t_map *map);
double				distance(double x1, double y1, double x2, double y2);
void				*ft_memcpy(void *dest, const void *src, size_t n);

//////INIT////////
void				init_rays(t_data *data, t_rays *first_ray,
						double ray_angle);
void				init_player(t_player *player, t_map *map);
t_data				*general_init(int ac, char **av);
int					check_space(char *str);

//////RGBs//////
unsigned int		get_pixel_color(t_texture *texture, void *addr, int x,
						int y);
void				my_mlx_pixel_put(t_data *data, double x, double y,
						int color);
int					create_rgb(int red, int green, int blue);
int					get_argb(char *c, t_data *data);
void				free_all_v2(t_data *data, int flag);

//// PARSING /////
int					file_validation(int arg, char **str);
t_parsing			*map_validation(int fd);
void				free_parser(t_parsing *parsing);

/// COLOR PARSER ////
char				**ft_split_color(char *s);
char				*detailer_color(char *color);
int					check_if_is_num(char *str);
int					check_dup(char **color, int indexer);
int					check_if_valid_number(char **str);
int					nearby(char **line);
int					getqomalen(char *str);
int					double_check(char *str);
int					final_check(char **color);
void				free_coloring(t_parsing *parsing);
int					fill_coloring(char **line, t_parsing *parsing);
char				**remove_empty(char **str);
/////////////////////

/// MAP PARSER /////
int					check_barrier(char **map);
void				free_all(t_data *data);
char				**ft_split_file(char *s, char c);
int					check_map_validation(char **map);
char				**ft_split_map(char *s);
int					get_r(char **map);
int					get_max_line(char **map);
int					player_check(char **map, int i, int j);
int					wall_check(char **map, int i, int j);
int					check_edge(char **map, int i, int j, char c);
int					check_corner(char **map, int i, int j, char c);
char				**replace_spaces_x(char **map, int maxlen);
int					invalid_sym(char **map);
int					map_components(char c);
int					player_position(char c);
int					edge_cases(char **map);
int					base_cases(char **map, int j, int i);
int					syntax_check(char **map);
double				deg_into_rad(char c);
char				player_id(char **map, int i, int j);
char				**fill_with_1(int max);
char				**resize(char **map, int max);
int					**convert_map(char **map, int len, int **data);
void				fill_int(char **map, t_map **map1, char **data);
int					getnlcount(char **str);
char				*ft_resize(char **map, int size, int i);
////////////////////

/// TEXTURES PARSER ///
int					check_file(char **line, int *files);
char				*textures(char *line);
int					check_for_combo(char **line);
t_parsing			*fill_texture(char **file_content, char *tmp);
void				free_textures(t_parsing *parsing);
int					get_len(char **s);
char				*textures(char *line);
int					check_spaces(char *str);
/////////////////////

/// APIS /////////
int					ft_strncmp(char *s1, char *s2, int n);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strchr(char *s, int c);
char				*ft_strjoin_map(char *result, char *buffer);
char				**ft_split(char *s);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t n);
void				ft_free(char **line);
int					ft_atoi(char *str);
size_t				ft_strlcpy(char *dest, char *src, size_t size);
char				*ft_substr(char *s, unsigned int start, size_t len);
int					is_space(char c);
int					map_parser(char *file, t_parsing *parsing);
/// NEXT_LINE ////
char				*get_next_line(int fd);
size_t				ft_strlen(char *s);
char				*get_new_line(char *s);
char				*ft_strdup(char *s1);
char				*ft_strjoin(char *s, char *s1);
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strchr(char *s, int c);
char				*set_buffer(char *buffer, char *line);
/////////////////

#endif
