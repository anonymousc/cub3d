/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 02:47:47 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/27 15:50:03 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void	free_textures(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(parsing->textures[i].direction);
		free(parsing->textures[i].filename);
		i++;
	}
	free(parsing->textures);
}

char	*textures(char *line)
{
	while (line && is_space(*line))
		line++;
	if (ft_strnstr(line, "NO ", 3))
		return ("NO");
	if (ft_strnstr(line, "SO ", 3))
		return ("SO");
	if (ft_strnstr(line, "WE ", 3))
		return ("WE");
	if (ft_strnstr(line, "EA ", 4))
		return ("EA");
	return (NULL);
}

int	check_file(char **line, int *files)
{
	int	fd;

	fd = 0;
	if (line[1])
	{
		fd = open(line[1], O_RDWR, 0666);
		(*files)++;
	}
	if (fd == -1)
		return (ft_free(line), -1);
	return (ft_free(line), close(fd), 0);
}

int	check_for_combo(char **line)
{
	int (j), (*index), (i);
	j = 0;
	i = 0;
	index = malloc(sizeof(int) * 4);
	while (line[i])
	{
		if (textures(line[i]))
		{
			index[j] = i;
			j++;
		}
		i++;
	}
	j = 0;
	while (j < 3)
	{
		if (index[j + 1] == index[j] + 1)
			j++;
		else
			return (free(index), 1);
	}
	return (free(index), 0);
}
