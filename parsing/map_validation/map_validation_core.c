/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_core.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:52:40 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/28 23:50:54 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

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
