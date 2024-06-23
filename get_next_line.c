/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:55:14 by mbozan            #+#    #+#             */
/*   Updated: 2024/06/23 18:20:21 by mbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*getline(char **stored)
{
	char	*line;
	char	*tmp;
	size_t	len;

	len = 0;
	while ((*stored)[len] && (*stored)[len] != '\n')
		len++;
	if ((*stored)[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	line[len] = '\0';
	while (len--)
		line[len] = (*stored)[len];
	tmp = ft_strjoin(*stored + len, "");
	free(*stored);
	*stored = tmp;
	return (line);
}

char	*readstore(int fd, char *stored)
{
	char		*buffer;
	char		*tmp;
	ssize_t		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(stored, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		tmp = ft_strjoin(stored, buffer);
		free(stored);
		stored = tmp;
	}
	free(buffer);
	return (stored);
}

char	*get_next_line(int fd)
{
	static char	*stored;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stored = readstore(fd, stored);
	if (!stored || !*stored)
		return (NULL);
	return (getline(&stored));
}
