/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:40:27 by fwhite42          #+#    #+#             */
/*   Updated: 2024/01/03 20:01:51 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	gnl_read_and_append(int fd, char **cache_address)
{
	int		bytes_read;
	char	*new_cache;
	size_t	cache_len;

	new_cache = NULL;
	cache_len = gnl_memory_len(*cache_address, "\0", 1);
	gnl_malloc(&new_cache, 0, cache_len + BUFFER_SIZE + 1);
	if (cache_len)
		gnl_memory_copy(new_cache, *cache_address, cache_len);
	bytes_read = read(fd, new_cache + cache_len, BUFFER_SIZE);
	gnl_malloc(cache_address, 0, 0);
	*cache_address = (new_cache);
	return (bytes_read);
}

int	gnl_split(char **src, char **dst)
{
	char	*new_src;
	char	*leftovers;
	size_t	new_src_len;
	size_t	src_len;

	new_src = NULL;
	leftovers = NULL;
	new_src_len = gnl_memory_len(*src, "\0\n", 2);
	src_len = gnl_memory_len(*src, "\0", 1);
	if (src_len == new_src_len)
		return (0);
	gnl_malloc(&new_src, 0, new_src_len + 2);
	gnl_malloc(&leftovers, 0, src_len - new_src_len + 1);
	gnl_memory_copy(new_src, *src, new_src_len + 1);
	gnl_memory_copy(leftovers, *src + new_src_len + 1, src_len - new_src_len);
	if (*src != *dst)
		gnl_malloc(dst, 0, 0);
	gnl_malloc(src, 0, 0);
	*src = new_src;
	*dst = leftovers;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*cache;
	int			keep_reading;

	cache = NULL;
	if (memory)
	{
		cache = memory;
		if (gnl_split(&cache, &memory))
			return (cache);
	}
	keep_reading = gnl_read_and_append(fd, &cache);
	while (keep_reading > 0)
	{
		if (gnl_split(&cache, &memory))
			return (cache);
		else
		{
			keep_reading = gnl_read_and_append(fd, &cache);
			if (keep_reading == 0)
				return (cache);
		}
	}
	return (cache);
}
