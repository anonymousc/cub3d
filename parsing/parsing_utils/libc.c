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
	if(!s)
		return NULL;
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
int	ft_strncmp(char *s1 ,char *s2, int n)
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
static size_t	ft_countword(char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == ',')
			s++;
		if (*s)
			count++;
		while (*s != ',' && *s)
			s++;
	}
	return (count);
}

static char	*get_next_word(char *s, size_t *len)
{
	char	*start;

	while (*s && *s == ',')
		s++;
	start = s;
	*len = 0;
	while (*s && *s != ',')
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

char	**ft_split_color(char *s)
{
	int		i;
	char	**lst;

	i = 0;
	if (!s)
		return (NULL);
	lst = split(s, i);
	return (lst);
}