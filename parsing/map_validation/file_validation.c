/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:30:09 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/28 19:20:47 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	check_barrier(char **map)
{
	int (i), (j);
	i = 0;
	j = 0;
	while (map[0][i])
	{
		if (check_edge(map, i, j, '0') || check_edge(map, i, j, 'N')
			|| check_edge(map, i, j, 'S') || check_edge(map, i, j, 'W')
			|| check_edge(map, i, j, 'E'))
			return (1);
		i++;
	}
	return (0);
}

void	extension_validation(char *str)
{
	if (ft_strlen(ft_strchr(str, '.')) != 4 || ft_strcmp(ft_strchr(str, '.'),
			".cub"))
		return (printf("Invalid map extension\n"), exit(1), (void)0);
}

int	file_validation(int arg, char **str)
{
	char	*check;
	int		fd;

	if (arg != 2)
	{
		printf("usage %s path_to or filename.cub", str[0]);
		exit(1);
	}
	fd = open(str[1], O_RDWR, 0666);
	if (fd == -1)
		return (printf("Error\n"), exit(1), 0);
	check = ft_strchr(str[1], '/') + 1;
	if (check)
	{
		extension_validation(check);
		return (fd);
	}
	else if (!check)
	{
		extension_validation(str[1]);
		return (fd);
	}
	return (0);
}
