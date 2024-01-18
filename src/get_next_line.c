/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:40:27 by fwhite42          #+#    #+#             */
/*   Updated: 2024/01/17 17:04:47 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	gnl_read_and_append(int fd, char **cache_address)
{
	int		bytes_read;
	char	*new_cache;
	size_t	cache_len;
	char	buffer[BUFFER_SIZE + 1];

	gnl_bzero(buffer, BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	cache_len = gnl_memory_len(*cache_address, "\0", 1);
	new_cache = NULL;
	gnl_config_memory(&new_cache, 0, cache_len + bytes_read + 1);
	if (new_cache)
	{
		gnl_memory_copy(new_cache, *cache_address, cache_len);
		gnl_memory_copy(new_cache + cache_len, buffer, bytes_read);
		gnl_config_memory(cache_address, cache_len, 0);
		*cache_address = (new_cache);
		return (bytes_read);
	}
	else
		return (-2);
}

int	gnl_split_cache_and_send2memory(char **cache, char **memory)
{
	size_t	cache_len;
	size_t	new_cache_len;
	size_t	new_memory_len;
	char	*new_cache;

	new_cache_len = gnl_memory_len(*cache, "\0\n", 2);
	cache_len = gnl_memory_len(*cache, "\0", 1);
	new_cache = NULL;
	new_memory_len = cache_len - new_cache_len;
	if (new_memory_len < 2)
		return (new_memory_len);
	gnl_config_memory(&new_cache, 0, new_cache_len + 1 + 1);
	gnl_memory_copy(new_cache, *cache, new_cache_len + 1);
	gnl_config_memory(memory, 0, new_memory_len);
	gnl_memory_copy(*memory, *cache + new_cache_len + 1, new_memory_len);
	gnl_config_memory(cache, cache_len, 0);
	*cache = new_cache;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*cache;
	int			bytes_read;

	cache = memory;
	if (cache)
	{
		memory = NULL;
		if (gnl_split_cache_and_send2memory(&cache, &memory))
			return (cache);
	}
	bytes_read = gnl_read_and_append(fd, &cache);
	if (bytes_read < 0)
	{
		gnl_config_memory(&cache, 0, 0);
		return (NULL);
	}
	if (bytes_read == 0)
		return (cache);
	memory = cache;
	return (get_next_line(fd));
}
