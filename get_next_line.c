
#include "get_next_line.h"

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
		return (NULL);
	}
	left_line = ft_substr(buffer, i + 1, ft_strlen(buffer) - (i + 1));
	free(buffer);
	return(left_line);
}
char	*get_line(char *buffer)
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
	if ( buffer[i] == '\n')
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

	temp = malloc(BUFFER_SIZE +1);
	if (!temp)
	return (NULL);
	bytes = 1;
	while(!(ft_strchr(buffer,'\n')) && bytes > 0)
	{
		tempbuffer = buffer;
		bytes = read(fd,temp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		temp[bytes] = '\0';
		buffer = ft_strjoin(tempbuffer, temp);
		free(tempbuffer);
	}
	return (free(temp),buffer);
}


char	*get_next_line(int fd)
{
	static char	*buffer;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_until_newline(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	if (!line)
		return (NULL);
	buffer = leftover_line(buffer);
	return (line);
}
/*#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("archivo.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return 0;
}*/