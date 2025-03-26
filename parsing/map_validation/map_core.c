/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:07:20 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/26 22:06:33 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static size_t	ft_countword(char *p)
{
	size_t		counter;
	int			in_word;
	int			i;

	i = 0;
	counter = 0;
	while (p && *p)
	{
		in_word = 0;
		if (*p == '\n' || in_word == 0 || *p)
		{
			in_word = 1;
			counter++;
		}
		p++;
	}
	return (counter);
}

static char	**split(char *s, int i)
{
	size_t	word_len;
	char	**lst;

	lst = (char **)malloc((ft_countword(s) + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	while (s && *s)
	{
		if (*s == '\n')
			s++;
		if (*s)
		{
			word_len = ft_strchr(s, '\n') - s;
			lst[i] = ft_substr(s, 0, word_len);
			i++;
			s += word_len;
		}
	}
	return (lst[i] = NULL, lst);
}

char	**ft_split_map(char *s)
{
	int		i;
	char	**lst;

	i = 0;
	if (!s)
		return (NULL);
	lst = split(s, i);
	return (lst);
}
int	get_max_line(char **map)
{
	int		i;
	size_t	max;

	i = 0;
	max = ft_strlen(map[i]);
	while (map[i])
	{
		if (max < ft_strlen(map[i]))
			max = ft_strlen(map[i]);
		i++;
	}
	return ((int)max);
}
char	*ft_resize(char *map, int size)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * (size + 1));
	while (i < size)
	{
		ret[i] = 'X';
		i++;
	}
	i = 0;
	while (map[i])
	{
		if (!is_space(map[i]))
			ret[i] = map[i];
		i++;
	}
	ret[size] = 0;
	return (ret);
}
char	**replace_spaces_X(char **map, int maxlen)
{
	int	i;

	i = 0;
	while (map[i])
	{
		map[i] = ft_resize(map[i], maxlen);
		i++;
	}
	return (map);
}
int check_corner(char **map, int i, int j, char c)
{
	return (
		(map[j][i + 1] == c && map[j][i] == 'X') ||
		(map[j][i + 1] == 'X' && map[j][i] == c) ||
		(map[j - 1][i] == 'X' && map[j][i] == c) ||
		(map[j - 1][i] == c && map[j][i] == 'X') ||
		(map[j + 1][i] == 'X' && map[j][i] == c) ||
		(map[j + 1][i] == c && map[j][i] == 'X')
	);
}
int check_edge(char **map, int i , int j, char c)
{
	return (
			map[j][ft_strlen(map[j]) - 1] == c ||
			map[get_len(map) - 1][i] == c ||
			map[0][i] == c ||
			(map[0][i] == 'X' && map[1][i] == c) ||
			(map[1][i] == 'X' && map[1][i + 1] == c) ||
			(map[1][i] == c && map[1][i + 1] == 'X')
		);
}
int wall_check(char **map, int i , int j)
{
	return (
		check_corner(map, i , j, '0') ||
		check_edge(map, i , j, '0')
		);
}
int player_check(char **map , int i , int j)
{
	return (
		check_corner(map, i , j, 'N') || 
		check_corner(map, i , j, 'S') || 
		check_corner(map, i , j, 'W') || 
		(check_corner(map, i , j, 'E') ||
		check_edge(map, i , j, 'N')) ||
		check_edge(map, i , j, 'S') ||
		check_edge(map, i , j, 'W') ||
		check_edge(map, i , j, 'E')
	);
}
int base_cases(char **map, int j , int i)
{
	return (
	  	wall_check(map , i , j) || player_check(map, i , j)
	);
}
int edge_cases(char **map)
{
	if(map[0] && map[1])
	{
		int i = 0;
		int j = 2;
		while (map[j])
		{
			i = 0;
			while(map[j][i])
			{
				if(map[j + 1] && map[j - 1] && map[j] && base_cases(map, j , i))
					return (1);
				if(map[j][i])
					i++;
			}
			if(map[j])
				j++;
		}

	}
	else
		return (1);
	return (0);
}
int player_position(char c)
{
	return (c == 'N' || c == 'W' || c == 'S' || c == 'E');
}
int map_components(char c)
{
	return (c == '1' || c == '0' || player_position(c) || is_space(c)); 
}
int invalid_sym(char **map)
{
	int i = 0;
	int player = 0;
	while(map[i])
	{
		int j = 0;
		while (map[i][j])
		{
			if(player_position(map[i][j]))
				player++;
			if(!map_components(map[i][j]))
				return (printf("here1\n"), 1);
			j++;
		}
		i++;
	}
	if (player != 1)
		return(printf("here1\n"), 1);
	return (0);
}
int	syntax_check(char **map)
{
	int	i;

	i = 0;
	if (get_len(map) < 3 || edge_cases(map)) 
		return (1);
	return (0);
}
int	check_map_validation(char **map)
{
	char **map_parser;

	map_parser = replace_spaces_X(map, get_max_line(map));
	if (syntax_check(map_parser) == 1)
		return ( 1);
	return (0);
}
double deg_into_rad(char c)
{
    if(c == 'N')
        return 0;
    if(c == 'E')
        return (PI / 2);
    if(c == 'S')
        return PI;
    if(c == 'W')
        return (3 * PI / 2);
    return 0;
}

char player_id(char **map, int i , int j)
{
	return (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E');
}
char **resize(char **map, int max , t_map * mapq)
{
	char **map1 = malloc(sizeof(char *) * (max + 1));
	int i = 0;
	while (i < max)
	{
		map1[i] = malloc(sizeof(char) * (max + 1));
		map1[i][max] = 0;	
		int j = 0;
		while (j < (max))
		{
			map1[i][j] = '1';
			j++;
		}
		map1[i][j] = 0;
		i++;
	}
	map1[i] = NULL;
	i = 0;
	while (map[i])
	{
		int j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != 'X')
				map1[i][j] = map[i][j];
			if(player_id(map, i , j))
				map1[i][j] = '0';
			j++;
		}
		i++;
	}
	return (map1);
}

int **convert_map(char **map, int len)
{
	int **data = malloc(sizeof(int *) * ((len) + 1));
	int i = 0;
	while (map[i])
	{
		data[i] = malloc(sizeof(int) * (len));
		int j = 0;
		while (j < len)
		{
			data[i][j] = map[i][j] - '0';
			j++;
		}
		i++;
	}
	data[i] = NULL;
	return (data);
	
}
int get_r(char **map)
{
	if(get_max_line(map) > get_len(map))
		return (get_max_line(map));
	else
		return (get_len(map));
		
}
int **fill_int(char **map, t_map *map1)
{
	int y = 0;
	while (map[y])
	{
		int x = 0;
		while (map[y][x])
		{
			if(player_position(map[y][x]))
			{
				map1->x = (double)(x * 64);
				map1->y  = (double)(y * 64);
				map1->n  = deg_into_rad(map[y][x]);
			}
				x++;
		}
		y++;
	}
	map = resize(map, get_r(map) , map1);
	map1->x_len = get_max_line(map);
	map1->y_len = get_max_line(map);
	int **data = convert_map(map , get_max_line(map));
	return (data);
}
t_map *fill_map(t_map *map , char **cords)
{
	map = malloc(sizeof(t_map));
	map->map = fill_int(cords, map);
	
	return (map);
}
int getnlcount(char **str)
{
	int i = 0;
	int count = 0;
	while(str[i])
	{
		if(*str[i] == '\n' || !str[i][0])
			count++;
		else
			return (count);
		i++;
	}
	return (count);
}
int getnlcount1(char **str)
{
	int i = 0;
	int count = 0;
	while(str[i])
	{
		if(*str[i] != '\n' || str[i][0])
			count++;
		i++;
	}
	return (count);
}
char **remove_newlines(char **map)
{
	char **map1 = malloc(sizeof(char *) * (getnlcount1(map) + 1));
	int i = 0;
	int j = 0;
	while (map[i])
	{
		if((*map[i] != '\n' || map[i][0]))
		{
			map1[j] = ft_strdup(map[i]);
			j++;
		}
		i++;	
	}
	map1[j] = NULL;
	return map1;
}
char **update_map_pos(char **map)
{
	int i = 0;
	i = 0;
	int max = 0;
	if(!map)
		return (NULL);
	while (map[i])
	{
		if(detailer_color(map[i]) || textures(map[i]))
			max = i + 1;
		if(map[i])
			i++;
	}
	map += max + getnlcount(map + max);
	map = remove_newlines(map);
	return (map);
	
}
int	map_parser(char *file, t_parsing *parsing)
{
	char	**map;
	map = ft_split_map(file);
	if(!map)
		return (1);
	map = update_map_pos(map);
	if (!map || invalid_sym(map) || check_map_validation(map) == 1)
		return (printf("Error\n"), 1);
	parsing->map = fill_map(parsing->map, map);
	return (0);
}