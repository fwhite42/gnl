/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:28:50 by fwhite42          #+#    #+#             */
/*   Updated: 2023/12/24 17:05:33 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"get_next_line.h"

#include<fcntl.h>
#include<stdio.h>

static void		gnl_memcpy(char *dst, char *memory, size_t linelen)
{
	while (linelen--)
		*(dst++) = *(memory++);
}

static void		gnl_read(int fd, char **buff, size_t *bufflen)
{
	printf("Reading with BUFFER_SIZE = %i\n", BUFFER_SIZE);
	*buff = (char *)malloc(BUFFER_SIZE + 1);
	*bufflen = read(fd, *buff, BUFFER_SIZE);
}

static void get_memory_length(char *memory, size_t *i)
{
	*i = 0;
	while(memory && memory[*i])
		(*i)++;
}

static void get_chunk_length(char *buff, size_t bufflen, char sep, size_t *chunklen)
{
	*chunklen = 0;
	while(*chunklen < bufflen && buff[*chunklen] != sep)
		(*chunklen)++;
	if (*chunklen < bufflen)
		(*chunklen)++;
}

static void		gnl_main(int fd, int depth, char **line, char **memory)
{
	printf("GNL MAIN > depth : %i\n", depth);
	size_t memlen;
	size_t chunklen;
	char *buff;
	char *trash;

	trash = NULL;
	printf("MEMORY[%p]<%s>\n",memory,*memory);
	get_memory_length(*memory, &memlen);
	if (memlen == 0)
	{
		if (*memory)
			trash = *memory + memlen - BUFFER_SIZE - 1; 
		printf("trash<%s>\n", trash);
		gnl_read(fd, memory, &memlen);
		printf("MEMORY_UPDATED[%p]<%s>\n",memory,*memory);
		if (!memlen)
			return ;
	}
	get_chunk_length(*memory, memlen, '\n', &chunklen);
	printf("CHUNK LENGTH: %zu\n", chunklen);
	*memory += chunklen;
	if (*line == NULL && *(*memory - 1) == '\n')
	{
		*line = (char *)malloc(depth * BUFFER_SIZE + chunklen + 1);
		printf("END OF LINE WAS FOUND IN MEMORY\n");
		(*line)[depth * BUFFER_SIZE + chunklen] = 0;
	}
	else if (*line == NULL)
		gnl_main(fd, depth + 1, line, memory);
	gnl_memcpy(*line + (BUFFER_SIZE * depth), buff, chunklen);
	printf("buff %s\n",buff);
	free(trash);
}

char *get_next_line(int fd)
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
	printf("Line<%s>\n", line);
}

//int			main(int ac, char **av)
int			main(void)
{
	int fd;
	char *filename;
	char *line;

	filename = "test";
	fd = open(filename, O_RDONLY);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);
	gnl_print(fd);

	return (0);
}
