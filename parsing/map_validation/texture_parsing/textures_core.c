/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_core.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:50:28 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/29 00:28:18 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	check_dup_tex(char **line)
{
    int		i;
    int		j;
    char	*(dir1),*(dir2);
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
	int	index;

	index = 0;
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

	int(i), (j);
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
	int(i), (j);
	parsing->textures = malloc(sizeof(t_tex) * TEXTURE_SIZE + 1);
	i = 0;
	j = 0;
	while (file_content[i])
	{
		if (textures(file_content[i]))
		{
			parsing->textures[j].direction = ft_strdup(textures(file_content[i]));
			j++;
		}
		i++;
	}
	parsing->textures = reduce(file_content, parsing->textures);
}

int check_spaces(char *str)
{
	size_t flag = 0;
	while (is_space(str[flag]))
	flag++;
	size_t i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		if (flag == ft_strlen(str) || ft_strlen(str) == 0)
			return (1);
		else
			return (0);
	}
	return (0);
}
int empty_line_count(char **str)
{
	int i = 0;
	int count = 0;
	while (str[i])
	{
		if (check_spaces(str[i]) || ft_strlen(str[i]) == 0)
			count++;
		i++;
	}
	return (count);
}
char **remove_empty(char **str)
{
	char **new;
	
	int i = 0;
	int j = 0;
	new = malloc(sizeof(char *) * (get_len(str)  - empty_line_count(str)) + 1);
	while (str[i])
	{
		if (!check_spaces(str[i]))
		{
			new[j] = ft_strdup(str[i]);
			j++;
		}
		i++;
	}
	new[j] = NULL;
	return (new);
}
t_parsing	*fill_texture(char **file_content, char *tmp)
{
	t_parsing	*parsing;

	char **texture = remove_empty(file_content);
	if (!texture)
		return (printf("File is empty !!\n"), NULL);
	if (check_textures(texture) == 0)
		return (ft_free(texture), free(tmp), printf("Error\n"), exit(1),
			NULL);
	parsing = malloc(sizeof(t_parsing));
	after_check(parsing, texture);
	return (parsing);
}
