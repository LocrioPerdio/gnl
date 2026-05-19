/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paduarte <paduarte@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 19:32:17 by paduarte          #+#    #+#             */
/*   Updated: 2026/05/19 19:34:10 by paduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// Is there space to incorporate ft_calloc instead of malloc?

static char *ft_read_and_store(int fd, char *buffer);
static char *ft_extract_line(char *buffer);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char *line;

    if (!buffer)
		buffer = ft_strdup("");
	line = NULL;
	buffer = ft_read_and_store(fd, buffer);
	line = ft_extract_line(buffer);
	return (line);
}

static char *ft_extract_line(char *buffer)
{
	char *line;
	size_t i;
	size_t j;	
	
	i = 0;
	j = 0;
	line = NULL;
	while(buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return(NULL);
	while(j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = '\0';	
	return(line);
}

static char *ft_read_and_store(int fd, char *buffer)
{
	int		bytes_read;
	char	*tmp;
	char	*total;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while(bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(tmp);
		return (NULL);
	}
	tmp[bytes_read] = '\0';
	total = ft_strjoin(buffer, tmp);
	buffer = total;
	free(buffer);
}
	free(tmp);
	return (buffer);
}


#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		count;
	char	*next_line;

	fd = open("example.txt", O_RDONLY);
	count = 0;
	while (count < 2)
	{
		next_line = get_next_line(fd);
		count++;
		if (next_line == NULL)
			break;
		printf("[%d]:%s\n", count, next_line);
		free(next_line);
	}
	next_line = NULL;
	close(fd);
	return (0);
}
