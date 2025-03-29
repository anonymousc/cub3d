/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_funct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-bou <aait-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:55:54 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/28 23:16:48 by aait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void	ft_free(char **line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

int	ft_atoi(char *str)
{
	long long	res;
	int			i;

	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if(!str[i])
		return (INT_MAX);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = (res * 10) + str[i++] - '0';
		if (res > UCHAR_MAX || res < 0)
			return (INT_MAX);
	}
	return (res);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack && n == 0)
		return (NULL);
	if (!(needle[j]))
	{
		return ((char *)&haystack[i]);
	}
	while (haystack && haystack[i])
	{
		while (haystack[i + j] == needle[j] && i + j < n)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	srcs;
	size_t	i;

	srcs = ft_strlen(src);
	i = 0;
	while (src && src[i] && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srcs);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start >= ft_strlen(s))
		return (ft_strdup(0x0));
	if (l - start >= len)
		s1 = (char *)malloc((len + 1));
	else
		s1 = (char *)malloc((l - start + 1));
	if (!s1)
		return (NULL);
	if (len >= SIZE_MAX)
		ft_strlcpy(s1, &s[start], l + 1);
	else
		ft_strlcpy(s1, (s + start), (len + 1));
	return (s1);
}
