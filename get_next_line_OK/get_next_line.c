#include "get_next_line.h"

char *get_next_line(int fd)
{
	char	buff[999999] = {0};
	int		i = 0;
	char	*res;

	if (fd < 0 || !BUFFER_SIZE)
		return (NULL);
	while (read(fd, &buff[i], 1) == 1)
	{
		if (buff[i] == '\n')
		{
			i++;
			break;
		}
		i++;
	}
	if (!buff[0])
		return (NULL);
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (buff[i])
	{
		res[i] = buff[i];
		i++;
	}
	free(buff);
	res[i] = '\0';
	return (res);
}
