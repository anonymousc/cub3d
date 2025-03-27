#include "Wolf3D.h"

void extension_validation(char *str)
{
	if(ft_strlen(ft_strchr(str , '.')) != 4 || ft_strcmp(ft_strchr(str , '.') , ".cub"))
		return (printf("Invalid map extension\n") ,exit(1), (void)0);
}

int file_validation(int arg,char **str)
{
	char *check;
	int fd;

	if(arg != 2)
	{
		printf("usage %s path_to or filename.cub", str[0]);
		exit (1);
	}
	fd = open(str[1] , O_RDWR, 0666);
	if(fd == -1)
		return (printf("Error\n") ,exit(1), 0);
    check = ft_strchr(str[1] , '/') + 1;
    if(check)
	{
	    extension_validation(check);
		return (fd);
	}
    else if(!check)
	{
        extension_validation(str[1]);
		return (fd);
	}
	return (0);
}
static size_t	ft_countword(char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == '\n')
			s++;
		if (*s)
			count++;
		while (*s != '\n' && *s)
			s++;
	}
	return (count);
}

static int	is_space_ret(char c)
{
	return (c == '\n');
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

char	**ft_split_file(char *s)
{
	int		i;
	char	**lst;

	i = 0;
	if (!s)
		return (NULL);
	lst = split(s, i);
	return (lst);
}