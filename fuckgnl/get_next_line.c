/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:40:27 by fwhite42          #+#    #+#             */
/*   Updated: 2024/01/02 22:51:14 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	gnl_read_and_append(int fd, char **data)
{
	int		bytes_read;
	char	*newdata;
	size_t	datalen;

	newdata = NULL;
	datalen = gnl_memory_len(*data, "\0", 1);
	gnl_malloc(&newdata, 0, datalen + BUFFER_SIZE + 1);
	gnl_memory_copy(newdata, *data, datalen);
	bytes_read = read(fd, newdata + datalen, BUFFER_SIZE);
	gnl_malloc(data, 0, 0);
	*data = (newdata);
	return (bytes_read);
}

int	gnl_split(char **data, char **memory)
{
	char	*line;
	char	*leftovers;
	size_t	line_len;
	size_t	data_len;

	line = NULL;
	leftovers = NULL;
	printf("data = <%s>\n", *data);
	printf("memory = <%s>\n", *memory);
	line_len = gnl_memory_len(*data, "\0\n", 2);
	data_len = gnl_memory_len(*data, "\0", 1);
	if (data_len == line_len)
		return (0);
	gnl_malloc(&line, 0, line_len + 2);
	gnl_malloc(&leftovers, 0, data_len - line_len + 1);
	gnl_memory_copy(line, *data, line_len + 1);
	gnl_memory_copy(leftovers, *data + line_len + 1, data_len - line_len);
	printf("LINE (%s)\n", line);
	printf("LEFTOVERS (%s)\n", leftovers);
	gnl_malloc(data, 0, 0);
	gnl_malloc(memory, 0, 0);
	free(*data);
	*data = line;
	*memory = leftovers;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*line;
	int			keep_going;

	line = memory;
	keep_going = gnl_read_and_append(fd, &line);
	while (keep_going)
	{
		if (gnl_split(&line, &memory))
			return (line);
		keep_going = gnl_read_and_append(fd, &line);
	}
	return (NULL);
}
