/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:38:57 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/27 15:54:27 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static size_t	ft_countword(char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (is_space(*s))
			s++;
		if (*s)
			count++;
		while (!is_space(*s) && *s)
			s++;
	}
	return (count);
}

static int	is_space_ret(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r');
}

static char	*get_next_word(char *s, size_t *len)
{
	char	*start;

	while (*s && is_space_ret(*s))
		s++;
	start = s;
	*len = 0;
	while (*s && !is_space_ret(*s))
	{
		(*len)++;
		s++;
	}
	return (start);
}

static char	**split(char *s, int i)
{
	size_t	word_count;
	size_t	len;
	char	**result;
	char	*word;

	word_count = ft_countword(s);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < (int)word_count)
	{
		word = get_next_word(s, &len);
		result[i] = ft_substr(word, 0, len);
		if (!result[i++])
			return (ft_free(result), NULL);
		s += (word - s) + len;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char *s)
{
	int		i;
	char	**lst;

	i = 0;
	if (!s)
		return (NULL);
	lst = split(s, i);
	return (lst);
}
