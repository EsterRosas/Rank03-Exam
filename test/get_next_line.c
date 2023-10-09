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

	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (1);
	return (0);
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	int		i = 0;

	str = malloc(count * size + 1);
	if (!str)
		return (NULL);
	while (str[i])
		str[i++] = 0;
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int	i = 0;
	int	j = 0;

	p = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));

	return (p);
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
		if (bytes_read = -1)
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
	char		*line = NULL;
	static char	*stored;
	int			bytes_read = 1;

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
