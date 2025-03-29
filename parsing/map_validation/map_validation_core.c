/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_core.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:52:40 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/29 02:59:29 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	getnlcount_check(char **str)
{
	int (i), (count);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strlen(str[i]) != 0 || !check_space(str[i]))
			count++;
		i++;
	}
	return (count);
}

int	getnlcount1(char **str)
{
	int (i), (count);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strlen(str[i]) == 0 || check_space(str[i]))
			count++;
		else
			break ;
		i++;
	}
	return (i);
}

t_parsing	*map_validation(int fd)
{
	static char	*line;
	char		*tmp;
	char		**file;
	t_parsing	*parsing;

	tmp = NULL;
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin_map(tmp, line);
		free(line);
		line = get_next_line(fd);
	}
	file = ft_split_file(tmp, '\n');
	parsing = fill_texture(file, tmp);
	if (fill_coloring(file, parsing) == 1)
		return (free(tmp), ft_free(file), free_textures(parsing), free(parsing),
			exit(1), NULL);
	if (map_parser(tmp, parsing) == 1)
		return (free(tmp), free_coloring(parsing), ft_free(file),
			free_textures(parsing), free(parsing), exit(1), NULL);
	ft_free(file);
	free(tmp);
	return (parsing);
}
