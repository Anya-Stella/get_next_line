/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:01:15 by tishihar          #+#    #+#             */
/*   Updated: 2024/07/05 15:51:57 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	char	find;

	find = (char)c;
	while (*s)
	{
		if (*s == find)
			return ((char *)s);
		s++;
	}
	if (find == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*(s++))
		count++;
	return (count);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (d > s && d < s + len)
	{
		d += len - 1;
		s += len - 1;
		while (len--)
			*(d--) = *(s--);
	}
	else
	{
		while (len--)
			*(d++) = *(s++);
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 + 1 >= SIZE_MAX - len2)
		return (NULL);
	p = malloc(len1 + len2 + 1);
	if (p == NULL)
		return (NULL);
	p[len1 + len2] = '\0';
	ft_memmove(p, s1, len1);
	ft_memmove(p + len1, s2, len2);
	return (p);
}

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	n;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	p = malloc(n + 1);
	if (p == NULL)
		return (NULL);
	p[n] = '\0';
	ft_memmove(p, s, n);
	return (p);
}
