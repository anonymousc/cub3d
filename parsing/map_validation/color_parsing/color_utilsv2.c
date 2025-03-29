/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utilsv2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 02:44:31 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/29 02:51:12 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	check_if_valid_number(char **str)
{
	int (i), (counter);
	i = 0;
	counter = 0;
	while (str[i])
	{
		if (ft_atoi(str[i]) == INT_MAX || check_if_is_num(str[i]))
			return (1);
		i++;
		counter++;
	}
	if (counter != 3)
		return (1);
	return (0);
}

int	double_check(char *str)
{
	char	**color_detailer;

	while (is_space(*str))
		str++;
	str += 1;
	if (!getqomalen(str))
		return (1);
	color_detailer = ft_split_color(str);
	if (!color_detailer || check_if_valid_number(color_detailer))
		return (ft_free(color_detailer), 1);
	return (ft_free(color_detailer), 0);
}

int	nearby(char **line)
{
	int (j), (*index), (i);
	j = 0;
	i = 0;
	index = malloc(sizeof(int) * 2);
	while (line[i])
	{
		if (detailer_color(line[i]))
		{
			index[j] = i;
			j++;
		}
		i++;
	}
	j = 0;
	while (j < 1)
	{
		if (index[j + 1] != index[j] + 1)
			return (free(index), 1);
		j++;
	}
	return (free(index), 0);
}

int	getqomalen(char *str)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		if (*str == ',')
			counter++;
		str++;
	}
	return (counter == 2);
}

int	final_check(char **color)
{
	int (i), (indexer);
	i = 0;
	indexer = 0;
	while (color[i])
	{
		if (detailer_color(color[i]))
		{
			indexer = i - 1;
			if (double_check(color[i]))
				return (1);
		}
		i++;
	}
	if (nearby(color))
		return (1);
	if (!check_dup(color, indexer))
		return (1);
	return (0);
}
