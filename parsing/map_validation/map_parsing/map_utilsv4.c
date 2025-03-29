/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilsv4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:23:24 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/29 03:17:34 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

char	**resize(char **map, int max)
{
	int		i;
	char	**map1;
	int		j;

	i = 0;
	map1 = fill_with_1(max);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != 'X')
				map1[i][j] = map[i][j];
			if (player_id(map, i, j))
				map1[i][j] = '0';
			j++;
		}
		i++;
	}
	return (map1);
}

int	**convert_map(char **map, int len, int **data)
{
	int	i;
	int	j;

	data = malloc(sizeof(int *) * ((len) + get_len(map) + 1));
	i = 0;
	while (map[i])
	{
		j = 0;
		data[i] = malloc(sizeof(int) * get_len(map));
		while (j < len)
		{
			data[i][j] = map[i][j] - '0';
			j++;
		}
		i++;
	}
	data[i] = NULL;
	ft_free(map);
	return (data);
}

int	get_r(char **map)
{
	if (get_max_line(map) > get_len(map))
		return (get_max_line(map));
	else
		return (get_len(map));
}

void	fill_int(char **map, t_map **map1, char **data)
{
	int (y), (x);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (player_position(map[y][x]))
			{
				(*map1)->x = (double)(x * 64);
				(*map1)->y = (double)(y * 64);
				(*map1)->n = deg_into_rad(map[y][x]);
			}
			x++;
		}
		y++;
	}
	(*map1)->x_len = get_max_line(data);
	(*map1)->y_len = get_max_line(data);
}

int	getnlcount(char **str)
{
	int (i), (count);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (*str[i] == '\n' || !str[i][0])
			count++;
		else
			return (count);
		i++;
	}
	return (count);
}
