/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:28:50 by fwhite42          #+#    #+#             */
/*   Updated: 2023/12/26 10:00:34 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"get_next_line.h"

#include<fcntl.h>
#include<stdio.h>

// Copies linelen bytes from memory to dst
static void	gnl_memcpy(char *dst, char *memory, size_t linelen)
{
	while (linelen--)
		*(dst++) = *(memory++);
}

// Allocates a *buff and reads from fd, writing *buff.
static void	gnl_read(int fd, char **buff, ssize_t *bl)
{
	*buff = (char *)malloc(BUFFER_SIZE + 1);
	if (*buff && fd >= 0)
	{
		*bl = read(fd, *buff, BUFFER_SIZE);
	}
}

// Computes the length of a string in memory
static void	get_memory_length(char *memory, ssize_t *i)
{
	*i = 0;
	while (memory && memory[*i])
		(*i)++;
}

// Computes the length of a 'sep'-terminating string. If the string 0-terminates
// before reaching 'sep', the length of the string is returned, otherwise the
// length of the 'sep'-terminating string is returned ('sep' partecipates in
// length of the string) 
static void	get_chunk_length(char *buff, size_t bl, char sep, size_t *cl)
{
	*cl = 0;
	while (*cl < bl && buff[*cl] != sep)
		(*cl)++;
	if (*cl < bl)
		(*cl)++;
}

static void	gnl_main(int fd, int depth, char **line, char **memory)
{
	ssize_t	ml;
	size_t	cl;
	char	*buff;
	char	*trash;

	trash = NULL;
	get_memory_length(*memory, &ml);
	if (ml == 0)
	{
		gnl_read(fd, memory, &ml);
		//printf("MEMORY<%s>\n", *memory);
		//printf("MEMORY_LENGTH<%zd>\n", ml);
		if (ml <= 0)
			return ;
		trash = *memory;
	}
	get_chunk_length(*memory, ml, '\n', &cl);
	buff = *memory;
	*memory += cl;
	if (*line == NULL && *(*memory - 1) == '\n')
	{
		*line = (char *)malloc(depth * BUFFER_SIZE + cl + 1);
		(*line)[depth * BUFFER_SIZE + cl] = 0;
	}
	else if (*line == NULL)
		gnl_main(fd, depth + 1, line, memory);
	gnl_memcpy(*line + (BUFFER_SIZE * depth), buff, cl);
	if (*memory == 0)
	{
		free(trash);
	}
}

char	*get_next_line(int fd)
{
	char *line;
	static char *memory;

	line = NULL; 
	gnl_main(fd, 0, &line, &memory);
	return line;
}

void gnl_print(int fd)
{
	char *line;
	line = get_next_line(fd);
	printf("LINE<%s>\n", line);
}
//int			main(int ac, char **av)
int			main(void)
{
	int fd;
	char *filename;
	char *line;
	gnl_print(100);
	filename = "test1";
	fd = open(filename, O_RDONLY);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);

	return (0);
}
