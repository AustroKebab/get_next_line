/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:56:37 by mbozan            #+#    #+#             */
/*   Updated: 2024/06/23 17:31:59 by mbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*news;
	size_t	i;
	size_t	i2;

	if (!s1 || !s2)
		return (NULL);
	news = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!news)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		news[i] = s1[i];
		i++;
	}
	i2 = 0;
	while (s2[i2])
	{
		news[i + i2] = s2[i2];
		i++;
		i2++;
	}
	news[i + i2] = '\0';
	return (news);
}
