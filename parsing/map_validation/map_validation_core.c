#include "Wolf3D.h"

t_parsing	*map_validation(int fd)
{
	static char	*line;
	char		*tmp;
	t_parsing	*parsing;

	tmp = NULL;
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin_map(tmp, line);
		free(line);
		line = get_next_line(fd);
	}
	char **file = ft_split_file(tmp);
	parsing = fill_texture(file , tmp);
	if (fill_coloring(file, parsing) == 1)
		return (free(tmp), ft_free(file) ,free_textures(parsing) 
		,free(parsing), exit(1) , NULL);
	if (map_parser(tmp, parsing) == 1)
		return (free(tmp),free_coloring(parsing) ,ft_free(file) , 
		free_textures(parsing), free(parsing),exit(1), NULL);
	ft_free(file);
	free(tmp);
	return (parsing);
}
