/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <wingstonetone9.8@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:01:50 by tishihar          #+#    #+#             */
/*   Updated: 2024/07/05 14:36:38 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_clean_remainder(char **remainderBox)
{
	free(*remainderBox);
	*remainderBox = NULL;
}
static int	ft_grow_remainder(int fd, char **remainderBox)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*new_remainder;

	while (!ft_strchr(*remainderBox, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read < 0 || **remainderBox == '\0')
				return (ft_clean_remainder(remainderBox), 0);
			break;
		}
		buffer[bytes_read] = '\0';
		new_remainder = ft_strjoin(*remainderBox, buffer);
		if (!new_remainder)
			return (ft_clean_remainder(remainderBox), 0);
		free(*remainderBox);
		*remainderBox = new_remainder;
	}
	return (1);
}




static char	*ft_extract_line(char **remainderBox)
{
	char	*end;
	char	*line;
	char	*new_remainder;

	end = ft_strchr(*remainderBox, '\n');
	if (end)
	{
		*end = '\0';
		line = ft_strjoin(*remainderBox, "\n");
		new_remainder = ft_strdup(end + 1);
		free(*remainderBox);
		*remainderBox = new_remainder;
	}
	else
	{
		line = ft_strdup(*remainderBox);
		ft_clean_remainder(remainderBox);
	}
	if ((end && !*remainderBox) || !line)
		{
			if (line)
				free(line);
			return(ft_clean_remainder(remainderBox), NULL);
		}
	return (line);
}





char	*get_next_line(int fd)
{
	static char	*remainder[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX) {
        return NULL;
    }

	if (!remainder[fd])
	{
		remainder[fd] = ft_strdup("");
		if (!remainder[fd])
			return (NULL);
	}
	if (!ft_grow_remainder(fd, &remainder[fd]))
		return (NULL);
	return (ft_extract_line(&remainder[fd]));
}