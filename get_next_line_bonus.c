/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moirhira <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:22:49 by moirhira          #+#    #+#             */
/*   Updated: 2024/11/14 14:22:51 by moirhira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Custom implementation of strdup
char	*my_strdup(char *src)
{
	char	*dup;
	int		len;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	len = calclen(src);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

// str convatination
void	ft_strcat(char *dest, const char *src)
{
	int	dest_len;
	int	i;

	dest_len = calclen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
}

// helper function in read from fd uppend data to buffer
char	*append_to_buffer(char *buffer, char *buf, int readed)
{
	char	*temp;

	if (!buffer)
		buffer = my_strdup(buf);
	else
	{
		temp = buffer;
		buffer = malloc(calclen(temp) + readed + 1);
		if (!buffer)
			return (NULL);
		ft_copy(buffer, temp);
		ft_strcat(buffer, buf);
		free(temp);
	}
	return (buffer);
}

// read from fd and add data to buffer until \n or end of file 
char	*readfromfd(int fd, char *buffer)
{
	char	*buf;
	int		readed;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	readed = read(fd, buf, BUFFER_SIZE);
	while (readed > 0)
	{
		if (readed == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[readed] = '\0';
		buffer = append_to_buffer(buffer, buf, readed);
		if (find_newline(buffer, '\n'))
			break ;
		readed = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (buffer);
}

//main function handle multiple fds
char	*get_next_line(int fd)
{
	static char		*buffers[1024];
	char			*line;

	if (!buffers[fd])
	{
		buffers[fd] = NULL;
	}
	if (!find_newline(buffers[fd], '\n'))
	{
		buffers[fd] = readfromfd(fd, buffers[fd]);
	}
	line = separate_line(buffers[fd]);
	buffers[fd] = update_buffer(buffers[fd]);
	return (line);
}
// #include <stdio.h>
// #include <fcntl.h>
// int main()
// {
//     char *s;
//     int fd = open("text.txt", O_RDONLY | O_CREAT);
// 	int fd1 = open("text1.txt", O_RDONLY | O_CREAT);
// 	int fd2 = open("text2.txt", O_RDONLY | O_CREAT);
//     if (fd == -1 || fd1 == -1|| fd2 == -1)
//     {
//         printf("Error opening file\n");
//         return 1;
//     }

// //    while( (s= get_next_line(fd)))
// //    {
//     printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd2));
// 	printf("%s", get_next_line(fd));
// //    }

//     close(fd);
//     return 0;
// }
