/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:55:14 by mbozan            #+#    #+#             */
/*   Updated: 2024/08/22 13:50:59 by mbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	nullfree(char **tofree)
{
	if (!tofree || !*tofree)
		return ;
	free(*tofree);
	*tofree = NULL;
}

char	*extractline(char **storage)
{
	char	*line;
	char	*nlinepos;
	char	*temp;

	if (!storage || !*storage)
		return (NULL);
	nlinepos = ft_strchr(*storage, '\n');
	if (nlinepos)
	{
		line = (char *)malloc(nlinepos - *storage + 2);
		if (!line)
			return (nullfree(storage), NULL);
		ft_strlcpy(line, *storage, nlinepos - *storage + 2);
		temp = ft_strdup(nlinepos + 1);
		if (!temp)
			return (nullfree(&line), nullfree(storage), NULL);
	}
	else
	{
		line = ft_strdup(*storage);
		temp = NULL;
	}
	nullfree(storage);
	return ((*storage = temp), line);
}

ssize_t	readstore(int fd, char **storage)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	if (!storage || !*storage)
		return (-1);
	buffer = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (nullfree(&buffer), -1);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*storage, buffer);
		if (!temp)
			return (nullfree(&buffer), -1);
		*storage = temp;
	}
	nullfree(&buffer);
	return (bytes_read);
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
		if (!storage)
			return (NULL);
	}
	while (!ft_strchr(storage, '\n'))
	{
		bytes_read = readstore(fd, &storage);
		if (bytes_read < 0 || (bytes_read == 0 && !*storage))
			return (nullfree(&storage), NULL);
		if (bytes_read == 0)
			break ;
	}
	line = extractline(&storage);
	if (line && (!storage || !*storage))
		nullfree(&storage);
	return (line);
}
