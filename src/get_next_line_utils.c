/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   get_next_line_utils.c                                   4 2              */
/*                                                        (@)-=-(@)           */
/*   By: fwhite42 <FUCK THE NORM>                          (  o  )            */
/*                                                       _/'-----'\_          */
/*   Created: 2024/02/01 13:13:57 by fwhite42          \\ \\     // //        */
/*   Updated: 2024/02/01 14:11:02 by fwhite42           _)/_\---/_\(_         */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

void	gnl_memory_copy(char *dst, char *src, size_t len)
{
	if (!src || !dst)
		return ;
	while (len--)
		*(dst++) = *(src++);
}

char	gnl_is_separator(char *sep_list, int sep_list_length, char x)
{
	while (sep_list_length--)
	{
		if (*(sep_list++) == x)
			return (1);
	}
	return (0);
}

size_t	gnl_memory_len(char *char_ptr, char *sep_list, int sep_list_length)
{
	size_t	len;

	len = 0;
	if (!char_ptr)
		return (0);
	while (!gnl_is_separator(sep_list, sep_list_length, *(char_ptr++)))
		len++;
	return (len);
}

void	gnl_bzero(char *target, size_t number_of_bytes)
{
	if (target)
	{
		while (number_of_bytes--)
			*(target++) = 0;
	}
}

int	gnl_config_memory(char **target, size_t old_size, size_t new_size)
{
	if (*target)
	{
		if (old_size)
			gnl_bzero(*target, old_size);
		free(*target);
		*target = NULL;
	}
	if (new_size)
	{
		*target = (char *)malloc(new_size);
		if (*target)
		{
			gnl_bzero(*target, new_size);
			return (1);
		}
		else
			return (-1);
	}
	else
		return (0);
}
