/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:35:47 by fwhite42          #+#    #+#             */
/*   Updated: 2023/12/30 18:32:47 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	gnl_get_chunk_length(t_gnl_buffer *buff)
{
	size_t	i;

	i = 0;
	while(i < buff->length && (buff->data)[i] != '\n')
		i++;
	return (i);
}

void	gnl_recursion(int fd, t_gnl_memory *memory, char **line, size_t linel)
{
	t_gnl_memory	*buff;
	char		*data;
	size_t		chunkl;
	size_t		offset;

	buff = gnl_read_cache(memory->cache, fd);
	if (buff == NULL || buff->offset == buff->length)
		buff = gnl_write_cache(memory->cache, fd);
	if (buff == NULL )
		return ((void) gnl_delete_cache(memory->cache, fd));
	data = buff->data;
	offset = buff->offset;
	chunkl = gnl_get_chunk_length(buff);
	linel += chunkl;
	buff->offset += chunkl;
	if (buff->offset < buff->length)
		*line = (char *)malloc(linel + 1);
	else
	{
		gnl_recursion(fd, memory, line, linel);
		gnl_collect_garbage(memory->garbage, data);
	}
	gnl_memory_copy(line + linel - chunkl, data + offset, cl);
}

char	*get_next_line(int fd)
{
	char			*line;
	static t_gnl_memory	memory;

	line = NULL;
	gnl_recursion(fd, &memory, line, 0);
	gnl_destroy_garbage(memory.garbage);
	return *line;
}
