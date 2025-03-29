/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:57:29 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/29 02:57:37 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	check_spaces(char *str)
{
	size_t	flag;

	flag = 0;
	while (is_space(str[flag]))
		flag++;
	if (flag == ft_strlen(str))
		return (1);
	return (0);
}

int	empty_line_count(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (check_spaces(str[i]))
			count++;
		i++;
	}
	return (count);
}

char	**remove_empty(char **str)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (get_len(str) - empty_line_count(str) + 1));
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
