/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paduarte <paduarte@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 19:32:17 by paduarte          #+#    #+#             */
/*   Updated: 2026/05/17 20:50:52 by paduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Is there space to incorporate ft_calloc instead of malloc?

char	*get_next_line(int fd)
{
	int		bytes_read;
	char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	// buffer[bytes_read] = '\0';
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
	while (1)
	{
		next_line = get_next_line(fd);
		count++;
		if (next_line == NULL)
			break ;
		printf("[%d]:%s\n", count, next_line);
		free(next_line);
	}
	next_line = NULL;
	close(fd);
	return (0);
}
