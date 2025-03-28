/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:07:20 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/27 15:45:06 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	getnlcount1(char **str)
{
	int(i), (count);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (*str[i] != '\n' || str[i][0])
			count++;
		i++;
	}
	return (count);
}

char	**remove_newlines(char **map, char **tmp)
{
	char	**map1;

	map1 = malloc(sizeof(char *) * (getnlcount1(map) + 1));
	int(i), (j);
	j = 0;
	i = 0;
	while (map[i])
	{
		if ((*map[i] != '\n' || map[i][0]))
		{
			map1[j] = ft_strdup(map[i]);
			j++;
		}
		i++;
	}
	map1[j] = NULL;
	ft_free(tmp);
	return (map1);
}

char	**update_map_pos(char **map)
{
	int		i;
	int		max;
	char	**tmp;

	if (!map)
		return (NULL);
	i = 0;
	max = 0;
	while (map[i])
	{
		if (detailer_color(map[i]) || textures(map[i]))
			max = i + 1;
		if (map[i])
			i++;
	}
	tmp = map + max + getnlcount(map + max);
	return (remove_newlines(tmp, map));
}

t_map	*fill_map(t_map *map, char **cords)
{
	char	**data;

	data = resize(cords, get_r(cords));
	fill_int(cords, &map, data);
	map->map = convert_map(data, get_max_line(cords), map->map);
	return (map);
}

int	map_parser(char *file, t_parsing *parsing)
{
	char	**map;
	char	**map1;

	map = ft_split_map(file);
	if (!map)
		return (1);
	map1 = update_map_pos(map);
	if (!map || invalid_sym(map1) || check_map_validation(map1) == 1)
		return (printf("Error\n"), ft_free(map1), 1);
	parsing->map = malloc(sizeof(t_map));
	parsing->map = fill_map(parsing->map, map1);
	ft_free(map1);
	return (0);
}
