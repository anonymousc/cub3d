/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:18:17 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/28 23:52:50 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

size_t	word_count(char *s, char c)
{
	size_t		counter;
	int			in_word;
	char	*p;

	if (s == NULL)
		return (0);
	counter = 0;
	in_word = 0;
	p = s;
	while (*p)
	{
		if (*p == c)
			in_word = 0;
		else if (in_word == 0)
		{
			counter++;
			in_word = 1;
		}
		p++;
	}
	return (counter);
}


char **fri_ol(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

static char	**str_all_fill(char **str, char *s, char c)
{
 char	*start;
	int			i;
	int			len;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			len = s - start;
			str[i] = (char *)malloc((len + 1) * sizeof(char));
			if (!str[i])
				return (fri_ol(str));
			ft_memcpy(str[i], start, len);
			str[i][len] = '\0';
			i++;
		}
		else
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split_file(char *s, char c)
{
	char		**str;

	if (!s)
		return (0);
	str = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (str_all_fill(str, s, c));
}
