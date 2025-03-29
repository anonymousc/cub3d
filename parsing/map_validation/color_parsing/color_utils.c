/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 02:41:18 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/28 23:25:27 by aait-bou         ###   ########.fr       */
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
	if ((ft_strnstr(color, "F", 2)))
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
		while (str[i] && is_space(str[i]))
			i++;
		if ((!(str[i] >= '0' && str[i] <= '9') && str[i]))
			return (1);
		if(str[i])
			i++;
	}
	return (0);
}
