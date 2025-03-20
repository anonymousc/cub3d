#include "Wolf3D.h"

void free_textures(t_parsing *parsing)
{
	int i = 0;
	while(i < 4)
	{
		free(parsing->textures[i].direction);
		free(parsing->textures[i].filename);
		i++;
	}
	free(parsing->textures);
	free(parsing);
}
char *textures(char *line)
{
	while(line && is_space(*line))
			line++;
	if(ft_strnstr(line ,"NO " , 3))
		return ("NO");
	if(ft_strnstr(line ,"SO ", 3))
		return ("SO");
	if(ft_strnstr(line ,"WE ", 3))
		return ("WE");
	if(ft_strnstr(line ,"EA ", 4))
		return ("EA");
	return (NULL);
}
static int check_file(char **line, int *files)
{
	static int j;
	int	fd;

	fd = 0;
	if(line[1])
	{
		fd = open(line[1], O_RDWR, 0666);
		j++;
	}
	if(fd == -1)
		return (ft_free(line),-1);
	*files = j;
	return (ft_free(line), close(fd), 0);
}
static int check_for_combo(char **line)
{
	int j , *index, i;

	j = 0;
	i = 0;
	index = malloc(sizeof(int) * 4);
	while (line[i])
	{
		if(textures(line[i]))
		{
			index[j] = i;
			j++;
		}
		i++;
	}
	j = 0;
	while (j < 3)
	{
		if(index[j + 1] == index[j] + 1)
			j++;
		else	
			return (free(index) ,1);
	}
	return (free(index), 0);
}
static int check_textures(char **line)
{
	int i;
	int counter;
	int files;
	int index = 0; 

	i = 0;
	counter = 0;
	files = 0;
	while (line && line[i])
	{
		if(textures(line[i]))
		{
			index = i;
			if(check_file(ft_split(line[i], ' '), &files) == -1 || i >= 6)
				return (0);
			counter++;
		}
		i++;
	}
	if(counter == 4 && files == 4 && check_for_combo(line) == 0)
		return (1);
	return (0);
}
static void after_check(t_parsing *parsing , char **file_content)
{
	int (i), (j);
	char **data;
	
	parsing->textures = malloc(sizeof(t_tex) * TEXTURE_SIZE + 1);
	i = 0;
	j = 0;
	while (file_content[i])
	{
		if(textures(file_content[i]))
		{
			parsing->textures[j].direction = ft_strdup(textures(file_content[i]));
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (file_content[i])
	{
		
		if(textures(file_content[i]))
		{
			data = ft_split(file_content[i], ' ');
			parsing->textures[j].filename = ft_strdup(data[1]);
			ft_free(data);
			j++;
		}
		i++;
	}
}

t_parsing *fill_texture(char **file_content)
{
	t_parsing *parsing;
	if(!file_content)
		return(printf("File is empty !!\n"), NULL);
	if(check_textures(file_content) == 0)
		return (printf("Error\n"), exit(1), NULL);
	parsing = malloc(sizeof(t_parsing));
	after_check(parsing , file_content);
	return (parsing); 
}