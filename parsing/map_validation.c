#include "Wolf3D.h"

int ft_atoi(char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = (res * 10) + str[i++] - '0';
		if (res > UCHAR_MAX || res < 0)
			return (INT_MAX);
	}
	return (res);
}
char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack && n == 0)
		return (NULL);
	if (!(needle[j]))
	{
		return ((char *)&haystack[i]);
	}
	while (haystack && haystack[i])
	{
		while (haystack[i + j] == needle[j] && i + j < n)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	srcs;
	size_t	i;

	srcs = ft_strlen(src);
	i = 0;
	while (src && src[i] && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srcs);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start >= ft_strlen(s))
		return (ft_strdup(0x0));
	if (l - start >= len)
		s1 = (char *)malloc((len + 1));
	else
		s1 = (char *)malloc((l - start + 1));
	if (!s1)
		return (NULL);
	if (len >= SIZE_MAX)
		ft_strlcpy(s1, &s[start], l + 1);
	else
		ft_strlcpy(s1, (s + start), (len + 1));
	return (s1);
}

static size_t	ft_countword(char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static char	**split(char *s, char c, int i)
{
	size_t	word_len;
	char	**lst;

	lst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			lst[i] = ft_substr(s, 0, word_len);
			i++;
			s += word_len;
		}
	}
	return (lst[i] = NULL, lst);
}

char	**ft_split(char *s, char c)
{
	int		i;
	char	**lst;

	i = 0;
	if (!s)
		return (NULL);
	lst = split(s, c, i);
	return (lst);
}
char *textures(char *line)
{
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

void ft_free(char **line)
{
	int i = 0;
	while (line && line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void *ft_bzero(void *set, int bytes)
{
	char *str = set;
	int i = -1;
	while (++i < bytes)
		str[i] = 0;
	return set;
}
int check_file(char **line, int *files)
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
		return (ft_free(line), fd);
	*files = j;
	return (ft_free(line), close(fd), 0);
}
int check_repeat(char **line)
{
	int i;

	i = 0;
	while (i < 4)
	{
		int j = 0;
		while (j < i)
		{
			if(textures(line[j]) == textures(line[j + 1]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
int check_textures(char **line)
{
	int i;
	int counter;
	int files;

	i = 0;
	counter = 0;
	files = 0;
	while (line && line[i])
	{
		if(textures(line[i]))
		{
			if(check_file(ft_split(line[i], ' '), &files) == -1 || i >= 6)
				return (ft_free(line), 0);
			counter++;
		}
		i++;
	}
	if(counter == 4 && files == 4 && check_repeat(line) != 1)
		return (1);
	else
		ft_free(line);
	return (0);
}
void after_check(t_parsing *parsing , char **file_content)
{
	int i;
	char **data;

	parsing->textures = malloc(sizeof(t_tex) * TEXTURE_SIZE + 1);
	i = 0;
	while (file_content[i])
	{
		if(textures(file_content[i]))
			parsing->textures[i].direction = ft_strdup(textures(file_content[i]));
		i++;
	}
	i = 0;
	while (file_content[i])
	{
		if(textures(file_content[i]))
		{
			data = ft_split(file_content[i], ' ');
			parsing->textures[i].filename = ft_strdup(data[1]);
			ft_free(data);
		}
		i++;
	}
}

t_parsing *fill_texture(char *line)
{
	char **file_content;
	t_parsing *parsing;

	file_content  = ft_split(line , '\n');
	if(!file_content)
		return(free(line), 
		printf("File is empty\n"), NULL);
	if(check_textures(file_content) == 0)
		return (printf("texture error\n"), 
		free(line), exit(1), NULL);
	parsing = malloc(sizeof(t_parsing));
	after_check(parsing , file_content);
	ft_free(file_content);
	return (parsing); 
}
char *detailer_color(char *color)
{
	if(ft_strnstr(color , "F ", 2))
		return ("F");
	if(ft_strnstr(color , "C ", 2))
		return ("C");
	return (NULL);
}
int get_len(char **s)
{
	int i = 0;
	while(s[i])
		i++;
	return (i);
}
int is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
int check_if_is_num(char *str)
{
	int i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	while (str[i])
	{
		if((str[i] >= '0' && str[i] <= '9') || !str[i])
			i++;
		else
		{
			printf("%c || %d\n", str[i], i);
			return (1);
		}
	}
	return (0);
}
int check_if_valid_number(char **str)
{
	int i = 0;
	char **detailed = ft_split(str[0] , ' ');
	if(detailed)
	{
		if(check_if_is_num(detailed[1]))
			return (1);
	}
	while (str[i])
	{
		if(ft_atoi(str[i]) == INT_MAX || check_if_is_num(str[i]))
			return (1);
		i++;
	}
	return (0);
}
int extra_check(char **color)
{
	int i = 0;
	int counter = 0;
	char **color_detailer;
	while (color[i])
	{
		if(detailer_color(color[i]))
		{
			if(i >= 6)
				return (1);
			counter++;
		}
		i++;
	}
	i = 0;
	while (color[i])
	{
		if(detailer_color(color[i]))
		{
			color_detailer = ft_split(color[i], ',');
			if(!color_detailer || get_len(color_detailer) != 3 || check_if_valid_number(color_detailer) == 1)
				return (ft_free(color_detailer), 1);
			ft_free(color_detailer);
		}
		i++;
	}
	if(counter == 2)
		return (0);
	return (1);
}
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
void free_coloring(t_parsing *parsing)
{
	int i = 0;
	while (i < parsing->coloring->iteration_level)
	{
		free(parsing->coloring->rgb);
		free(parsing->coloring->surface);
		i++;
	}
	free(parsing->coloring);
}
int *fill_rgb(char **str, t_color *color)
{
	int i = 0;
	int j = 0;
	color->rgb = malloc(sizeof(int) * (COLOR_SIZE + 1));
	while (str[i])
	{
		color->rgb[j] = ft_atoi(str[i]);
		j++;
		i++;
	}
	color->rgb[j] = 0;
	ft_free(str);
	return (color->rgb);
}
int fill_coloring(char *line, t_parsing *parsing)
{
	char **color;
	char **data;

	color = ft_split(line , '\n');
	if(extra_check(color) == 1)
		return (ft_free(color), printf("Error colors\n"), 1);
	int i = 0;
	parsing->coloring = malloc(sizeof(t_color) * 2);
	parsing->coloring->iteration_level = 2;
	while (color[i])
	{
		if(detailer_color(color[i]))
			parsing->coloring[i].surface = ft_strdup(detailer_color(color[i]));
		i++;
	}
	i = 0;
	while (color[i])
	{
		if(detailer_color(color[i]))
		{
			data = ft_split(color[i], ' ');
			if(!data)
				return (free_coloring(parsing) ,ft_free(color), 1);
			parsing->coloring->rgb = fill_rgb(ft_split(data[1] , ','), &parsing->coloring[i]);
			ft_free(data);
		}	
		i++;
	}
	return (0);
}

char *map_validation(int fd)
{
    static char *line;
	char *tmp;
	t_parsing *parsing;

	tmp = NULL;
	line = get_next_line(fd);
    while(line)
	{
		tmp = ft_strjoin_map(tmp,  line);
		free(line);
		line = get_next_line(fd);
	}
	parsing = fill_texture(tmp);
	if(fill_coloring(tmp , parsing) == 1)
		return(free_textures(parsing),free(tmp) ,NULL);
	exit(1);
    return (tmp);
} 

