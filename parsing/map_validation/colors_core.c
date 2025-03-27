#include "Wolf3D.h"

void free_coloring(t_parsing *parsing)
{
	int i = 0;
	if(parsing)
	{
		while (i < 2)
		{
			free(parsing->coloring[i].rgb);
			free(parsing->coloring[i].surface);
			i++;
		}
		free(parsing->coloring);
	}
}

char *detailer_color(char *color)
{
	while(is_space(*color))
			color++;
	if(ft_strnstr(color , "F ", 2))
		return ("F");
	if(ft_strnstr(color , "C ", 2))
		return ("C");
	return (NULL);
}

int get_len(char **s)
{
	int i = 0;
	while(s && s[i])
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
	while (str[i])
	{
		if((str[i] >= '0' && str[i] <= '9') || is_space(str[i]) ||  !str[i])
			i++;
		else
			return (1);
	}	
	return (0);
}
int check_if_valid_number(char **str)
{
	int i = 0;
	int counter = 0;
	while (str[i])
	{
		if(ft_atoi(str[i]) == INT_MAX || check_if_is_num(str[i]))
			return (1);
		i++;
		counter++;
	}
	if(counter != 3)
		return 1;
	return (0);
}
static int nearby(char **line)
{
	int j , *index, i;

	j = 0;
	i = 0;
	index = malloc(sizeof(int) * 2);
	while (line[i])
	{
		
		if(detailer_color(line[i]))
		{
			index[j] = i;
			j++;
		}
		i++;
	}
	j = 0;
	while (j < 1)
	{
		if(index[j + 1] == index[j] + 1)
			j++;
		else	
			return (free(index) ,1);
	}
	return (free(index), 0);
}
int getqomalen(char *str)
{
	int counter = 0;
	while(*str)
	{
		if(*str == ',')
			counter++;
		str++;
	}
	return (counter == 2);
}

int double_check(char *str)
{
	char **color_detailer;
	while (is_space(*str))
		str++;
	str += 1;
	if(!getqomalen(str))
		return (1);
	color_detailer = ft_split_color(str);
	if(!color_detailer || check_if_valid_number(color_detailer))
		return (ft_free(color_detailer), 1);
	return (ft_free(color_detailer), 0);
}
int check_dup(char **color, int indexer)
{
	return (*color[indexer] == *color[indexer + 1]);
}
int final_check(char **color)
{
	int i = 0;
	int indexer = 0;
	while (color[i])
	{
		if(detailer_color(color[i]))
		{
			indexer = i - 1;
			if(double_check(color[i]))
				return (1);
		}
		i++;
	}
	if(nearby(color) || check_dup(color, indexer))
		return (1);
	return (0);
}
int extra_check(char **color)
{
	int (i), (counter);

	i = 0;
	counter = 0;
	while (color[i])
	{
		if(color[i] && detailer_color(color[i]))
		{
			if(i >= 6)
				return (1);
			counter++;
		}
		i++;
	}
	if(counter == 2 && final_check(color) == 0)
		return (0);
	return (1);
}
int *fill_rgb(char **str)
{
	int i = 0;
	int *rgb = malloc(sizeof(int) * (COLOR_SIZE));
	while (str[i])
	{
		rgb[i] = ft_atoi(str[i]);
		i++;
	}
	ft_free(str);
	return (rgb);
}

int fill_coloring(char **color, t_parsing *parsing)
{
	char **data;

	if(extra_check(color) == 1)
		return (printf("Error\n"), 1);
	int i = 0;
	int j = 0;
	parsing->coloring = malloc(sizeof(t_color) * 2);
	while (color[i])
	{
		if(detailer_color(color[i]))
		{
			parsing->coloring[j].surface = ft_strdup(detailer_color(color[i]));
			j++;
		}
		i++;
	}
	i = 0;
	j = 0;
	while (color[i])
	{
		if(detailer_color(color[i]))
		{
			data = ft_split(color[i]);
			if(!data)
				return (free_coloring(parsing) ,ft_free(color), 1);
			parsing->coloring[j].rgb = fill_rgb(ft_split_color(data[1]));
			ft_free(data);
			j++;
		}	
		i++;
	}
	return (0);
}