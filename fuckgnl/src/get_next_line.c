/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:40:27 by fwhite42          #+#    #+#             */
/*   Updated: 2024/01/04 21:41:44 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	gnl_read_and_append(int fd, char **cache_address)
{
	int		bytes_read;
	char	*new_cache;
	size_t	cache_len;
	char	buffer[BUFFER_SIZE + 1];
	int		i;

	i = 0;
	new_cache = NULL;
	while (i < BUFFER_SIZE + 1)
		buffer[i++] = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	cache_len = gnl_memory_len(*cache_address, "\0", 1);
	gnl_config_memory(&new_cache, 0, cache_len + bytes_read + 1);
	if (new_cache)
	{
		gnl_memory_copy(new_cache + cache_len, buffer, bytes_read);
		gnl_memory_copy(new_cache, *cache_address, cache_len);
		gnl_config_memory(cache_address, 0, 0);
		*cache_address = (new_cache);
	}
	return (bytes_read);
}

int	gnl_split_cache_and_send2memory(char **cache, char **memory)
{
	char	*new_cache;
	char	*new_memory;
	size_t	new_cache_len;
	size_t	new_memory_len;
	size_t	cache_len;

	new_cache = NULL;
	new_memory = NULL;
	new_cache_len = gnl_memory_len(*cache, "\0\n", 2);
	cache_len = gnl_memory_len(*cache, "\0", 1);
	new_memory_len = cache_len - new_cache_len;
	if (cache_len == new_cache_len)
		return (0);
	gnl_config_memory(&new_cache, 0, new_cache_len + 1 + 1);
	gnl_config_memory(&new_memory, 0, new_memory_len + 1);
	gnl_memory_copy(new_cache, *cache, new_cache_len + 1);
	gnl_memory_copy(new_memory, *cache + new_cache_len + 1, new_memory_len);
	if (*cache != *memory)
		gnl_config_memory(memory, 0, 0);
	gnl_config_memory(cache, 0, 0);
	*cache = new_cache;
	*memory = new_memory;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*cache;
	int			bytes_read;
	int			new_line_char_was_found;

	cache = memory;
	new_line_char_was_found = gnl_split_cache_and_send2memory(&cache, &memory);
	if (new_line_char_was_found)
		return (cache);
	bytes_read = gnl_read_and_append(fd, &cache);
	if (bytes_read <= 0)
	{
		gnl_config_memory(&memory, 0, 0);
		return (cache);
	}
	new_line_char_was_found = gnl_split_cache_and_send2memory(&cache, &memory);
	if (new_line_char_was_found)
		return (cache);
	memory = cache;
	return (get_next_line(fd));
}
