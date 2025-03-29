/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:50:28 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/29 02:57:19 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	check_dup_tex(char **line)
{
	int	i;
	int	j;

	char *(dir1), *(dir2);
	i = 0;
	while (line[i])
	{
		if (textures(line[i]))
		{
			j = i + 1;
			dir1 = textures(line[i]);
			while (line[j])
			{
				if (textures(line[j]))
				{
					dir2 = textures(line[j]);
					if (ft_strcmp(dir1, dir2) == 0)
						return (0);
				}
				j++;
			}
		}
		i++;
	}
	return (1);
}

static int	check_textures(char **line)
{
	int	i;
	int	counter;
	int	files;

	i = 0;
	counter = 0;
	files = 0;
	while (line && line[i])
	{
		if (textures(line[i]))
		{
			if (check_file(ft_split(line[i]), &files) == -1 || i >= 6)
				return (0);
			counter++;
		}
		i++;
	}
	if (counter == 4 && files == 4 && check_for_combo(line) == 0
		&& check_dup_tex(line))
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
	char		**texture;

	if (!file_content)
		return (printf("File is empty !!\n"), NULL);
	texture = remove_empty(file_content);
	if (check_textures(texture) == 0)
		return (ft_free(texture), free(tmp), \
		ft_free(file_content), printf("Error\n"), exit(1), NULL);
	parsing = malloc(sizeof(t_parsing));
	after_check(parsing, texture);
	ft_free(texture);
	return (parsing);
}
