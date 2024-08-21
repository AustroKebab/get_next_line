/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbozan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:56:37 by mbozan            #+#    #+#             */
/*   Updated: 2024/08/21 23:16:52 by austrokebab      ###   ########.fr       */
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

char	*ft_strjoin(char *storage, char *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!storage || !s2)
		return (NULL);
	new_str = (char *)malloc(ft_strlen(storage) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (storage[i])
	{
		new_str[i] = storage[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	if (new_str)
		nullfree(&storage);
	return (new_str);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	i;

	if (!s1)
		return (NULL);
	copy = (char *)malloc(ft_strlen(s1) + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (s && *s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (s && *s == (char)c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < size -1)
	{
		dst[i] = src[i];
		++i;
	}
	if (size > 0)
		dst[i] = 0;
	while (src[i])
		++i;
	return (i);
}
