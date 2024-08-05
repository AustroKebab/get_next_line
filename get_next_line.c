/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:55:14 by mbozan            #+#    #+#             */
/*   Updated: 2024/08/05 17:27:45 by mbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>
#define DEBUG_ALLOC(ptr) printf("ALLOCATED: %p\n", (void *)(ptr))
#define DEBUG_FREE(ptr) printf("FREED: %p\n", (void *)(ptr))

static char	*extractline(char **storage)
{
	char	*line;
	char	*nlinepos;
	char	*temp;
	size_t	len;

	nlinepos = ft_strchr(*storage, '\n');
	if (nlinepos)
	{
		len = nlinepos - *storage + 1;
		line = (char *)malloc(len + 1);
		DEBUG_ALLOC(line);
		if (!line)
			return (NULL);
		ft_strlcpy(line, *storage, len + 1);
		temp = ft_strdup(nlinepos + 1);
		DEBUG_ALLOC(temp);
		if (!temp)
			return (free(line), DEBUG_FREE(line), NULL);
	}
	else
	{
		line = ft_strdup(*storage);
		temp = NULL;
	}
	free(*storage);
	DEBUG_FREE(*storage);
	*storage = temp;
	return (line);
}

static ssize_t	readstore(int fd, char **storage)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	DEBUG_ALLOC(buffer);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*storage, buffer);
		DEBUG_ALLOC(temp);
		if (!temp)
			return (free(buffer), DEBUG_FREE(buffer), -1);
		*storage = temp;
	}
	free(buffer);
	DEBUG_FREE(buffer);
	return (bytes_read);
}

static void	storefree(char **nullstore)
{
	if (nullstore && *nullstore)
	{
		free(*nullstore);
		DEBUG_FREE(*nullstore);
		*nullstore = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!storage)
	{
		storage = ft_strdup("");
		DEBUG_ALLOC(storage);
		if (!storage)
			return (NULL);
	}
	while (!ft_strchr(storage, '\n'))
	{
		bytes_read = readstore(fd, &storage);
		if (bytes_read < 0 || (bytes_read == 0 && !*storage))
			return (storefree(&storage), NULL);
		if (bytes_read == 0)
			break ;
	}
	line = extractline(&storage);
	return (line);
}
