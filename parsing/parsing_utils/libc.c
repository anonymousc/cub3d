/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:31:21 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/27 15:55:48 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

char	*ft_strjoin(char *result, char *buffer)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!result)
	{
		result = (char *)malloc(1 * sizeof(char));
		if (!result)
			return (NULL);
		result[0] = '\0';
	}
	if (!result || !buffer)
		return (NULL);
	line = malloc(ft_strlen(result) + ft_strlen(buffer) + 1);
	if (!line)
		return (NULL);
	i = -1;
	j = 0;
	while (result[++i] != '\0')
		line[i] = result[i];
	while (buffer[j] != '\0')
		line[i++] = buffer[j++];
	line[ft_strlen(result) + ft_strlen(buffer)] = '\0';
	free(result);
	return (line);
}

char	*ft_strchr(char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin_map(char *s, char *s1)
{
	char	*p;
	char	*str;
	int		i;

	i = 0;
	if (!s && !s1)
		return (NULL);
	p = (char *)malloc(ft_strlen(s) + ft_strlen(s1) + 1);
	if (!p)
		return (free(s), NULL);
	p[ft_strlen(s) + ft_strlen(s1)] = '\0';
	str = p;
	if (s)
		while (s[i])
			*(p++) = s[i++];
	i = 0;
	if (s1)
		while (s1[i])
			*(p++) = s1[i++];
	free(s);
	return (str);
}
