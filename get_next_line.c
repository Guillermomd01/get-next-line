/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gumunoz <gumunoz@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:36:57 by gumunoz           #+#    #+#             */
/*   Updated: 2025/10/21 15:37:02 by gumunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	s;

	i = 0;
	s = ft_strlen(src);
	if (size == 0)
		return (s);
	while (src[i] && i < size -1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (s);
}

char	*leftover_line(char *buffer)
{
	char	*left_line;
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] != '\n')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	left_line = ft_substr(buffer, i + 1, ft_strlen(buffer) - (i + 1));
	free (buffer);
	return (left_line);
}

char	*extract_line(char *buffer)
{
	int		i;
	char	*line;
	int		len;

	i = 0;
	len = 0;
	if (buffer == NULL || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		len = i + 1;
	else
		len = i;
	line = ft_substr(buffer, 0, len);
	return (line);
}

char	*read_until_newline(int fd, char *buffer)
{
	char	*temp;
	int		bytes;
	char	*tempbuffer;

	if (!buffer)
		buffer = ft_strdup("");
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(buffer, '\n') && bytes > 0)
	{
		tempbuffer = buffer;
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
			return (free(temp),free(buffer),NULL);
		temp[bytes] = '\0';
		buffer = ft_strjoin(tempbuffer, temp);
		free(tempbuffer);
		if (!buffer)
			return (free(temp), NULL);
	}
	return (free(temp), buffer);
}


char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_until_newline(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = leftover_line(buffer);
	return (line);
}
	// #include <fcntl.h>
	// #include <stdio.h>
	// #include "get_next_line.h"

	// int main(void)
	// {
	// 	int fd = open("archivo.txt", O_RDONLY);
	// 	char *line;

	// 	while ((line = get_next_line(fd)) != NULL)
	// 	{
	// 		printf("%s", line);
	// 		free(line);
	// 	}

	// 	close(fd);
	// 	return 0;
	// }
