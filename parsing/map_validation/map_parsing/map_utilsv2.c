/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilsv2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:19:37 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/28 01:27:40 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

char	**replace_spaces_x(char **map, int maxlen)
{
	int		i;
	maxlen = get_r(map);
	char	**to_rem;

	i = 0;
	to_rem = (char **)malloc(sizeof(char *) * (get_r(map) + 1));
	while (i < get_r(map))
	{
		to_rem[i] = ft_resize(map, maxlen, get_len(map));
		i++;
	}
	to_rem[i] = NULL;
	return (to_rem);
}

int	check_corner(char **map, int i, int j, char c)
{
	return (
		(map[j][i + 1] == c && map[j][i] == 'X')
		|| (map[j][i + 1] == 'X' && map[j][i] == c) 
		|| (map[j - 1][i] == 'X' && map[j][i] == c)
		|| (map[j - 1][i] == c && map[j][i] == 'X') 
		|| (map[j + 1][i] == 'X' && map[j][i] == c)
		|| (map[j + 1][i] == c && map[j][i] == 'X')
		||  map[j][ft_strlen(map[j]) - 1] == c 
		|| 	map[get_len(map) - 1][i] == c 
		||	map[j][0] == c
	);
}

int	check_edge(char **map, int i, int j, char c)
{
	(void)j;

	return (
		map[1][ft_strlen(map[1]) - 1] == c 
		|| 	map[get_len(map) - 1][i] == c 
		||	map[0][i] == c 
		|| (map[0][i] == 'X' && map[1][i] == c)
		|| (map[1][i] == 'X' && map[1][i + 1] == c) 
		|| (map[1][i] == c && map[1][i + 1] == 'X')
	);
}

int	wall_check(char **map, int i, int j)
{
	return (check_edge(map, i, j, '0') || check_corner(map, i, j, '0'));
}

int	player_check(char **map, int i, int j)
{
	return (
		((check_corner(map, i, j, 'N'))
		|| (check_corner(map, i, j, 'S'))
		|| (check_corner(map, i, j, 'W'))
		|| ((check_corner(map, i, j, 'E') 
		|| check_edge(map, i, j, 'N')
		|| check_edge(map, i, j, 'S')
		|| check_edge(map, i, j, 'W')
		|| check_edge(map, i, j, 'E'))
	)));
}
