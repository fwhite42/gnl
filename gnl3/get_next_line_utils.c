/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:34:24 by fwhite42          #+#    #+#             */
/*   Updated: 2023/12/30 18:32:43 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void gnl_recursion(int fd, char **line, t_gnl_memory memory)
{
	t_gnl_buffer *buff;
	size_t chunklen;

	buff = *gnl_read_cache(memory.cache, fd);
	if (buff == NULL)
	   buff = *gnl_write_cache(memory.cache, fd);	
	chunklen = get_chunk_length(buff);
	buff->linelength += chunklen;
}

t_gnl_buffer *gnl_write_cache(t_list *cache, int fd)
{
	t_gnl_buffer *buff;
	
	*buff = malloc(sizeof(t_gnl_buffer));
	buff->fd = fd;
	buff->data = malloc(BUFFER_SIZE);
	buff->length = 0;
	buff->offset = 0;
	buff->linelength = 0;
	if (cache == NULL)
		*cache = (t_list *)malloc(sizeof(t_list));
	cache->content = (void *)buff;
	cache->next = NULL;
}

t_gnl_buffer *gnl_read_cache(t_list *cache, int fd)
{
	t_gnl_buffer *buff;
	while (cache != NULL)
	{
		buff = (t_gnl_buffer *)(cache->content);
		if (buff->fd == fd)
			return buff;
		cache = cache->next;
	}
	buff = NULL;
	return buff;
}
