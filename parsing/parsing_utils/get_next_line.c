/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:30:35 by aessadik          #+#    #+#             */
/*   Updated: 2025/02/12 23:05:59 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

static char	*process_left(char *result)
{
	int		i;
	char	*line;

	i = 0;
	if (!result || !result[i])
		return (NULL);
	while (result[i] != '\0' && result[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1 + (result[i] == '\n')));
	if (!line)
		return (NULL);
	i = 0;
	while (result[i] && result[i] != '\n')
	{
		line[i] = result[i];
		i++;
	}
	if (result[i] == '\n')
	{
		line[i] = result[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*process_right(char *result)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (result[i] && result[i] != '\n')
		i++;
	if (!result[i])
		return (free(result), NULL);
	line = malloc((ft_strlen(result) - i + 1) * sizeof(char));
	if (!line)
		return (free(line), NULL);
	i++;
	j = 0;
	while (result[i])
		line[j++] = result[i++];
	line[j] = '\0';
	free(result);
	return (line);
}

static char	*read_til_newline(int fd, char *result)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(result, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(result);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		result = ft_strjoin(result, buffer);
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result = read_til_newline(fd, result);
	if(!result)
		return (NULL);
	line = process_left(result);
	result = process_right(result);
	
	return (line);
}
