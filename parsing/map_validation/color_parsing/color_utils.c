/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 02:41:18 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/28 21:18:35 by aessadik         ###   ########.fr       */
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

int check_dup(char **color, int indexer) {
    int flag = 0;
    int flag1 = 0;

    while (is_space(color[indexer][flag])) {
        flag++;
    }

    while (is_space(color[indexer + 1][flag1])) {
        flag1++;
    }
    return (ft_strncmp(color[indexer] + flag, color[indexer + 1] + flag1, 1));
}

int	check_if_is_num(char *str)
{
	int	i;

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
