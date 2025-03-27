/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 02:41:18 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/27 02:43:57 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void	free_coloring(t_parsing *parsing)
{
	int	i;

	i = 0;
	i = 0;
	if (parsing)
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
char	*detailer_color(char *color)
{
	while (is_space(*color))
		color++;
	if (ft_strnstr(color, "F ", 2))
		return ("F");
	if (ft_strnstr(color, "C ", 2))
		return ("C");
	return (NULL);
}

int	get_len(char **s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	check_dup(char **color, int indexer)
{
	return (*color[indexer] == *color[indexer + 1]);
}

int	check_if_is_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || is_space(str[i]) || !str[i])
			i++;
		else
			return (1);
	}
	return (0);
}