/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilsv3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:21:06 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/29 02:54:35 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	base_cases(char **map, int j, int i)
{
	return (wall_check(map, i, j) || player_check(map, i, j));
}

int	edge_cases(char **map)
{
	int (i), (j);
	i = 0;
	j = 2;
	if (check_barrier(map))
		return (1);
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j + 1] && map[j - 1] && map[j] && base_cases(map, j, i))
				return (1);
			if (map[j][i])
				i++;
		}
		if (map[j])
			j++;
	}
	return (0);
}

int	player_position(char c)
{
	return (c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

int	map_components(char c)
{
	return (c == '1' || (c == '0' || c == 'N') || c == 'W' || c == 'S'
		|| c == 'E' || is_space(c) || c == 0);
}

int	invalid_sym(char **map)
{
	int (i), (j), (player);
	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (player_position(map[i][j]))
				player++;
			if (!map_components(map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	if (player != 1)
		return (1);
	return (0);
}
