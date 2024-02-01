/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   get_next_line.c                                         4 2              */
/*                                                        (@)-=-(@)           */
/*   By: fwhite42 <FUCK THE NORM>                          (  o  )            */
/*                                                       _/'-----'\_          */
/*   Created: 2024/02/01 13:51:10 by fwhite42          \\ \\     // //        */
/*   Updated: 2024/02/01 16:14:34 by fwhite42           _)/_\---/_\(_         */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	gnl_read_and_append(int fd, char **cache_address)
{
	int		bytes_read;
	char	*new_cache;
	size_t	cl;
	char	buffer[BUFFER_SIZE + 1];

	gnl_bzero(buffer, BUFFER_SIZE + 1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	cl = gnl_memory_len(*cache_address, "\0", 1);
	new_cache = NULL;
	gnl_config_memory(&new_cache, 0, cl + bytes_read + 1);
	if (new_cache)
	{
		gnl_memory_copy(new_cache, *cache_address, cl);
		gnl_memory_copy(new_cache + cl, buffer, bytes_read);
		gnl_config_memory(cache_address, cl, 0);
		*cache_address = (new_cache);
		return (bytes_read);
	}
	else
	{
		gnl_config_memory(cache_address, cl, 0);
		return (-2);
	}
}

int	gnl_split_cache_and_send2memory(char **cache, char **memory)
{
	size_t	cl;
	size_t	ncl;
	char	*new_cache;

	ncl = gnl_memory_len(*cache, "\0\n", 2);
	cl = gnl_memory_len(*cache, "\0", 1);
	new_cache = NULL;
	if (cl - ncl < 2)
		return (cl - ncl);
	if (gnl_config_memory(&new_cache, 0, ncl + 1 + 1) >= 0)
	{
		if (gnl_config_memory(memory, 0, cl - ncl) > 0)
		{
			gnl_memory_copy(new_cache, *cache, ncl + 1);
			gnl_memory_copy(*memory, *cache + ncl + 1, cl - ncl);
			gnl_config_memory(cache, cl, 0);
			*cache = new_cache;
			return (1);
		}
		gnl_config_memory(&new_cache, 0, 0);
	}
	gnl_config_memory(cache, cl, 0);
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*cache;
	int			success;
	int			bytes_read;

	cache = memory;
	if (cache)
	{
		memory = NULL;
		success = gnl_split_cache_and_send2memory(&cache, &memory);
		if (success < 0)
			return (NULL);
		else if (success)
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
