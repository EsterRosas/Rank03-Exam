#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i = 0;

	while (s[i])
		i++;
	return (i);
}

int	has_eol(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (1);
	return (0);
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i = 0;
	size_t	len = count * size;

	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
		str[i++] = 0;
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int	i = 0;
	int	j = 0;

	if (!s1)
	{
		s1 = ft_calloc(1, sizeof(char));
		s1[0] = '\0';
	}
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	free (s1);
	return (p);
}

char	*upd_stored(char *st)
{
	int		i = 0;
	int		j = 0;
	char	*new_st;

	if (!st)
		return (NULL);
	while (st[i] && st[i] != '\n')
		i++;
	if (!st[i])
	{
		free (st);
		return (NULL);
	}
	new_st = ft_calloc(ft_strlen(st) - i + 1, sizeof(char));
	if (!new_st)
		return (NULL);
	i++;
	while (st[i + j])
	{
		new_st[j] = st[i + j];
		j++;
	}
	free (st);
	return (new_st);
}

char	*get_line(char	*str)
{
	char	*res;
	int		i = 0;
	
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	res = ft_calloc(i + 2, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		res[i] = '\n';
		res[i + 1] = '\0';
	}
	else
		res[i] = '\0';
	return (res);
}

char	*go_read(int fd, char *s_read)
{
	int		bytes_read = 1;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (bytes_read > 0 && !has_eol(s_read))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		s_read = ft_strjoin(s_read, buffer);
	}
	free(buffer);
	return (s_read);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stored;

	if (!BUFFER_SIZE || fd < 0)
		return (NULL);
	stored = go_read(fd, stored);
	if (!stored)
	{
		free(stored);
		return (NULL);
	}
	line = get_line(stored);
	stored = upd_stored(stored);
	return (line);
}
