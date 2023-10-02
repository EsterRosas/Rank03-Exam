#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int		i = 0;
	int		rd = 0;
	char	*buffer = malloc(100000);
	char	character;

	if (BUFFER_SIZE < 1)
		return (NULL);
	rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1);
	buffer[i++] = character;
	if (character != '\n')
	{
		while (rd > 0)
		{
			buffer[i++] = character;
			if (character == '\n')
				break ;
			rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1);
		}
	}
	buffer[i] = '\0';
	if (rd == -1 || i == 0 || (!rd && !buffer[i - 1]))
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
