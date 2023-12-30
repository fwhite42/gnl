/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:28:50 by fwhite42          #+#    #+#             */
/*   Updated: 2023/12/29 16:19:07 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"get_next_line.h"


typedef struct s_buffer {
	void *start;
	size_t offset;
	size_t size;
}	t_buffer;

typedef struct s_node {
	int fd;
	t_buffer *buffer;
	t_node *next;
}	t_node;

gnl_memory_set(t_node *node, int fd, char *buffer, size_t length)
{
	*new_node = malloc(sizeof(t_buffer))
	node->fd = fd;
	new_node->buffer = buffer;
	nenode->length = length;
	node->next = NULL;
}

static void	gnl_main(int fd, char **line, char **memory, int line_length)
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
		if (ml <= 0)
			return ;
		trash = *memory;
	}
	get_chunk_length(*memory, ml, '\n', &cl);
	buff = *memory;
	*memory += cl;
	if (*line == NULL && *(*memory - 1) == '\n')
	{
		*line = (char *)malloc(line_length + cl + 1);
		(*line)[line_length + cl] = 0;
	}
	else if (*line == NULL)
		gnl_main(fd, line, memory, line_length + cl);
	gnl_memcpy(*line + line_length, buff, cl);
	if (**memory == 0)
	{
		free(trash);
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*memory;

	line = NULL;
	gnl_main(fd, &line, &memory, 0);
	return (line);
}
