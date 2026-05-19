/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paduarte <paduarte@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 19:32:17 by paduarte          #+#    #+#             */
/*   Updated: 2026/05/19 23:29:43 by paduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Is there space to incorporate ft_calloc instead of malloc?

static char	*ft_read_and_store(int fd, char *buffer);
static char	*ft_extract_line(char *buffer);
static char	*ft_save_rest(char *buffer);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	line = NULL;
	buffer = ft_read_and_store(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_extract_line(buffer);
	buffer = ft_save_rest(buffer);
	return (line);
}

static char	*ft_extract_line(char *buffer)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	line = NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_save_rest(char *buffer)
{
	char	*new_buffer;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	new_buffer = NULL;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc((ft_strlen(buffer) - i) + 1);
	if (!new_buffer)
		return (NULL);
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

static char	*ft_read_and_store(int fd, char *buffer)
{
	int		bytes_read;
	char	*tmp;
	char	*total;

	bytes_read = 1;
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (free(buffer), NULL);
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(tmp), free(buffer), NULL);
		tmp[bytes_read] = '\0';
		total = ft_strjoin(buffer, tmp);
		free(buffer);
		buffer = total;
	}
	free(tmp);
	if (buffer && buffer[0] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*next_line;

	fd = open("example.txt", O_RDONLY);
	next_line = get_next_line(fd);
	while (next_line)
	{
		printf("%s", next_line);
		free(next_line);
		next_line = get_next_line(fd);
	}
	next_line = NULL;
	close(fd);
	return (0);
}
*/
