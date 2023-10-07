/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:33:01 by erosas-c          #+#    #+#             */
/*   Updated: 2023/10/07 13:19:27 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(char *s, int c)
{
	while (*s != '\0' && (char)c != *s)
		s++;
	if ((char)c == *s)
		return (s);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	i;
	size_t	len;

	i = 0;
	len = count * size;
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*p;

	i = -1;
	j = -1;
	if (!s1)
	{
		s1 = ft_calloc(sizeof (char), 1);
		s1[0] = '\0';
	}
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (NULL);
	while (s1[++i])
		p[i] = s1[i];
	while (s2[++j])
		p[i + j] = s2[j];
	p[i + j] = '\0';
	free(s1);
	return (p);
}

char	*upd_stored(char	*p)
{
	int		i;
	int		j;
	char	*next_stored;

	i = 0;
	j = -1;
	while (p[i] && p[i] != '\n')
		i++;
	if (!p[i])
	{
		free(p);
		return (NULL);
	}
	next_stored = ft_calloc(sizeof(char), ft_strlen(p) - i + 1);
	if (!next_stored)
		return (NULL);
	i++;
	while (p[i + (++j)])
		next_stored[j] = p[i + j];
	free(p);
	return (next_stored);
}

char	*get_line(char *p)
{
	int		i;
	char	*line;

	i = 0;
	if (!p[i])
		return (NULL);
	while (p[i] && p[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (p[++i] && p[i] != '\n')
		line[i] = p[i];
	if (p[i] == '\n')
	{
		line[i] = p[i];
		line[i + 1] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

char	*go_read(int fd, char *read_s)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		read_s = ft_strjoin(read_s, buffer);
	}
	free(buffer);
	return (read_s);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stored;

	if (fd < 0)
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
