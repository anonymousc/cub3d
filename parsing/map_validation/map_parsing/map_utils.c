/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:12:09 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/28 01:27:00 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

int	get_max_line(char **map)
{
	int		i;
	size_t	max;

	i = 0;
	max = ft_strlen(map[i]);
	while (map[i])
	{
		if (max < ft_strlen(map[i]))
			max = ft_strlen(map[i]);
		i++;
	}
	return ((int)max);
}

char	*ft_resize(char **map, int size, int overflow)
{
	int		i;
	char	*ret;
	static int data;

	ret = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
	{
		ret[i] = 'X';
		i++;
	}
	ret[i] = 0;
	i = 0;
	if(data <= overflow)
	{
		while (map[data] && map[data][i])
		{
			if (!is_space(map[data][i]))
			ret[i] = map[data][i];
			i++;
		}
	}
	data++; 
	return (ret);
}

static size_t	ft_countword(char *p)
{
	size_t	counter;
	int		in_word;
	int		i;

	i = 0;
	counter = 0;
	while (p && *p)
	{
		in_word = 0;
		if (*p == '\n' || in_word == 0 || *p)
		{
			in_word = 1;
			counter++;
		}
		p++;
	}
	return (counter);
}

static char	**split(char *s, int i)
{
	size_t	word_len;
	char	**lst;

	lst = (char **)malloc((ft_countword(s) + 1) * sizeof(char *));
	if (!lst)
		return (NULL);
	while (s && *s)
	{
		if (*s == '\n')
			s++;
		if (*s)
		{
			word_len = ft_strchr(s, '\n') - s;
			lst[i] = ft_substr(s, 0, word_len);
			i++;
			s += word_len;
		}
	}
	return (lst[i] = NULL, lst);
}

char	**ft_split_map(char *s)
{
	int		i;
	char	**lst;

	i = 0;
	if (!s)
		return (NULL);
	lst = split(s, i);
	return (lst);
}
