#include "Wolf3D.h"

int ft_strlen(char *str)
{
	int i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i);
}
char	*ft_strchr(char *s, int c)
{
	int	i;
	int	len;

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
int	ft_strcmp(char *s1 ,char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
void extension_validation(char *str)
{
	if(ft_strlen(ft_strchr(str , '.')) != 4 || ft_strcmp(ft_strchr(str , '.') , ".cub"))
		return (printf("Invalid map extension\n") ,exit(1), (void)0);
}

void file_validation(int arg,char **str)
{
	if(arg != 2)
	{
		printf("usage %s path_to or filename.cub", str[0]);
		exit (1);
	}
	int fd = open(str[1] , O_RDWR);
	if(fd == -1)
		return (close(fd) ,printf("Invalid file\n") ,exit(1), (void)0);
    char *check = ft_strchr(str[1] , '/') + 1;
    if(check)
	    extension_validation(check);
    else
        extension_validation(str[1]);
	// close(fd);
}
