/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:50:28 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/27 15:52:23 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	check_dup_tex(char **line, int index)
{
	int	i;
	int	j;

	i = index - 3;
	while (i < index)
	{
		while (is_space(*line[i]))
			line++;
		j = index - 3;
		while (j <= i)
		{
			if (*line[j] == *line[j + 1])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_textures(char **line)
{
	int	i;
	int	counter;
	int	files;
	int	index;

	index = 0;
	i = 0;
	counter = 0;
	files = 0;
	while (line && line[i])
	{
		if (textures(line[i]))
		{
			index = i;
			if (check_file(ft_split(line[i]), &files) == -1 || i >= 6)
				return (0);
			counter++;
		}
		i++;
	}
	if (counter == 4 && files == 4 && check_for_combo(line) == 0
		&& !check_dup_tex(line, index))
		return (1);
	return (0);
}

t_tex	*reduce(char **file_content, t_tex *texture)
{
	char	**data;

	int (i), (j);
	i = 0;
	j = 0;
	while (file_content[i])
	{
		if (textures(file_content[i]))
		{
			data = ft_split(file_content[i]);
			texture[j].filename = ft_strdup(data[1]);
			ft_free(data);
			j++;
		}
		i++;
	}
	return (texture);
}

static void	after_check(t_parsing *parsing, char **file_content)
{
	int (i), (j);
	parsing->textures = malloc(sizeof(t_tex) * TEXTURE_SIZE + 1);
	i = 0;
	j = 0;
	while (file_content[i])
	{
		if (textures(file_content[i]))
		{
			parsing->textures[j].direction = \
				ft_strdup(textures(file_content[i]));
			j++;
		}
		i++;
	}
	parsing->textures = reduce(file_content, parsing->textures);
}

t_parsing	*fill_texture(char **file_content, char *tmp)
{
	t_parsing	*parsing;

	if (!file_content)
		return (printf("File is empty !!\n"), NULL);
	if (check_textures(file_content) == 0)
		return (ft_free(file_content), free(tmp), printf("Error\n"), exit(1),
			NULL);
	parsing = malloc(sizeof(t_parsing));
	after_check(parsing, file_content);
	return (parsing);
}
