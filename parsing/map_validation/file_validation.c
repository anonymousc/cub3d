/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:30:09 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/27 18:11:06 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void	extension_validation(char *str)
{
	if (ft_strlen(ft_strchr(str, '.')) != 4 || ft_strcmp(ft_strchr(str, '.'),
			".cub"))
		return (printf("Invalid map extension\n"), exit(1), (void)0);
}

int	file_validation(int arg, char **str)
{
	char	*check;
	int		fd;

	if (arg != 2)
	{
		printf("usage %s path_to or filename.cub", str[0]);
		exit(1);
	}
	fd = open(str[1], O_RDWR, 0666);
	if (fd == -1)
		return (printf("Error\n"), exit(1), 0);
	check = ft_strchr(str[1], '/') + 1;
	if (check)
	{
		extension_validation(check);
		return (fd);
	}
	else if (!check)
	{
		extension_validation(str[1]);
		return (fd);
	}
	return (0);
}
