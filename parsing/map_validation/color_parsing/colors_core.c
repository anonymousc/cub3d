/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:40:35 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/29 00:29:48 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	extra_check(char **color)
{
	int(i), (counter), (flag);
	i = 0;
	counter = 0;
	flag = 0;
	while (color[i])
	{
		if (detailer_color(color[i]))
		{
			if (i>= 6)
				return (1);
			counter++;
		}
		i++;
	}
	if (counter == 2 && !final_check(color))
		return (0);
	return (1);
}

int	*fill_rgb(char **str)
{
	int	i;
	int	flag;
	int	*rgb;

	i = 0;
	flag = 0;
	rgb = malloc(sizeof(int) * (COLOR_SIZE));
	while (str[i])
	{
		flag = 0;
		if (i == 0)
		{
			while (is_space(str[0][flag]))
				flag++;
			flag++;
		}
		rgb[i] = ft_atoi(str[i] + flag);
		i++;
	}
	ft_free(str);
	return (rgb);
}

t_color	*extra_norm(t_color *coloring, char **color)
{
	char	*data;

	int(i), (j);
	i = 0;
	j = 0;
	while (color[i])
	{
		if (detailer_color(color[i]))
		{
			data = ft_strdup(color[i]);
			coloring[j].rgb = fill_rgb(ft_split_color(data));
			free(data);
			j++;
		}
		i++;
	}
	return (coloring);
}
static int check_spaces(char *str)
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
static int empty_line_count(char **str)
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
static char **remove_empty(char **str)
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
	char **coloring = remove_empty(color);
	if (extra_check(coloring) == 1)
		return (printf("Error\n"), 1);
	parsing->coloring = after_parse(coloring, parsing->coloring);
	return (0);
}
