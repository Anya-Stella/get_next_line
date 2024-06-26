/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:50:42 by tishihar          #+#    #+#             */
/*   Updated: 2024/06/26 20:41:09 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);

// kokokesu
#define BUFFER_SIZE 42

static void	ft_grow_remainder(int fd, char **remainderBox)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*new_remainder;

	while (!ft_strchr(*remainderBox, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			// error hundling
			free(*remainderBox);
			*remainderBox = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		new_remainder = ft_strjoin(*remainderBox, buffer);
		free(*remainderBox);
		*remainderBox = new_remainder;
	}
}
char	*ft_extract_line(char **remainderBox)
{
	char	*end;
	char	*line;
	char	*new_remainder;

	end = ft_strchr(*remainderBox, '\n');
	if (end)
	{
		end = '\0';
		line = ft_strdup(*remainderBox);
		new_remainder = ft_strdup(end + 1);
		free(remainderBox);
		*remainderBox = new_remainder;
	}
	else
	{
		// last handling
		line = ft_strdup(*remainderBox);
		free(*remainderBox);
		*remainderBox = NULL;
	}
	return (line);
}
char	*get_next_line(int fd)
{
	static char	*remainder;

	if (!*remainder)
		remainder = ft_strdup("");
	ft_grow_remainder(fd, &remainder);
	// extract_oneline
	return (ft_extract_line(&remainder));
}
