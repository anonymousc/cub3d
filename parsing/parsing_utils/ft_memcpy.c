/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 02:51:28 by aessadik          #+#    #+#             */
/*   Updated: 2025/03/29 02:59:56 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wolf3D.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (dest == src)
		return (dest);
	str1 = (unsigned char *)src;
	str2 = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		str2[i] = str1[i];
		i++;
	}
	return (dest);
}
