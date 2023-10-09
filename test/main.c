#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <unistd.h>

int	main()
{
	int	fd = open("fle.txt", O_RDONLY);
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else
			printf("line: %s\n", line);
	}
	return (0);
}
