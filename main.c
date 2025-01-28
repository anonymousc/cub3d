#include "Cub3D.h"

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
char	*ft_strchr(char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
char	*ft_strnstr(char *haystack, char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack || n == 0)
		return (NULL);
	if (!(needle[j]))
		return ((char *)&haystack[i]);
	while (haystack && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < n)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
void extension_validation(char *str)
{
	if(ft_strlen(ft_strchr(str , '.')) != 4)
	{
		printf("data == %s || %s\n", str ,ft_strchr(str , '.'));
		return (printf("Invalid map extension\n") ,exit(1), (void)0);
	}
}

void file_validation(int arg,char **str)
{
	if(arg != 2)
	{
		printf("usage %s path_to or filename.cub", str[0]);
		exit (1);
	}
	extension_validation(str[1]);
	int fd = open(str[1] , O_RDWR);
	if(fd == -1)
		return (close(fd) ,printf("Invalid file\n") ,exit(1), (void)0);
	close(fd);
}

int main(int ac , char **av)
{
	file_validation(ac, av);
}
