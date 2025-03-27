/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilsv1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:28:16 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/27 15:49:29 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

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
	char	**map_parser;

	map_parser = replace_spaces_x(map, get_max_line(map));
	if (!map_parser || syntax_check(map_parser) == 1)
		return (ft_free(map_parser), 1);
	return (ft_free(map_parser), 0);
}

double	deg_into_rad(char c)
{
	if (c == 'N')
		return (0);
	if (c == 'E')
		return (PI / 2);
	if (c == 'S')
		return (PI);
	if (c == 'W')
		return (3 * PI / 2);
	return (0);
}

char	player_id(char **map, int i, int j)
{
	return (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
		|| map[i][j] == 'E');
}

char	**fill_with_1(int max)
{
	char	**map;
	int		i;
	int		j;

	map = NULL;
	i = 0;
	map = malloc(sizeof(char *) * (max + 1));
	while (i < max)
	{
		map[i] = malloc(sizeof(char) * (max + 1));
		map[i][max] = 0;
		j = 0;
		while (j < (max))
		{
			map[i][j] = '1';
			j++;
		}
		map[i][j] = 0;
		i++;
	}
	map[i] = NULL;
	return (map);
}
