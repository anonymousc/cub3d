#include "Wolf3D.h"

int	extra_check(char **color)
{
	int(i), (counter);
	i = 0;
	counter = 0;
	while (color[i])
	{
		if (color[i] && detailer_color(color[i]))
		{
			if (i >= 6)
				return (1);
			counter++;
		}
		i++;
	}
	if (counter == 2 && final_check(color) == 0)
		return (0);
	return (1);
}

int	*fill_rgb(char **str)
{
	int	i;
	int	*rgb;

	i = 0;
	rgb = malloc(sizeof(int) * (COLOR_SIZE));
	while (str[i])
	{
		rgb[i] = ft_atoi(str[i]);
		i++;
	}
	ft_free(str);
	return (rgb);
}

t_color	*extra_norm(t_color *coloring, char **color)
{
	char	**data;

	int(i), (j);
	i = 0;
	j = 0;
	while (color[i])
	{
		if (detailer_color(color[i]))
		{
			data = ft_split(color[i]);
			coloring[j].rgb = fill_rgb(ft_split_color(data[1]));
			ft_free(data);
			j++;
		}
		i++;
	}
	return (coloring);
}

t_color	*after_parse(char **color, t_color *coloring)
{
	int(i), (j);
	i = 0;
	j = 0;
	coloring = malloc(sizeof(t_color) * 2);
	while (color[i])
	{
		if (detailer_color(color[i]))
		{
			coloring[j].surface = ft_strdup(detailer_color(color[i]));
			j++;
		}
		i++;
	}
	coloring = extra_norm(coloring, color);
	return (coloring);
}

int	fill_coloring(char **color, t_parsing *parsing)
{
	if (extra_check(color) == 1)
		return (printf("Error\n"), 1);
	parsing->coloring = after_parse(color, parsing->coloring);
	return (0);
}
