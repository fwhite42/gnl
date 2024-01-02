/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:42:51 by fwhite42          #+#    #+#             */
/*   Updated: 2024/01/02 22:51:01 by fwhite42         ###   ########.fr       */
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

size_t	gnl_memory_length(char *char_ptr, char *sep_list, int sep_list_length)
{
	size_t	len;

	len = 0;
	if (!char_ptr)
		return (0);
	while (!gnl_is_separator(sep_list, sep_list_length, *(char_ptr++)))
		len++;
	return (len);
}

void	gnl_malloc(char **target, size_t oldsize, size_t newsize)
{
	size_t	i;

	i = 0;
	if (*target)
	{
		if (oldsize)
		{
			while (i < oldsize)
				(*target)[i++] = 0;
		}
		free(*target);
		*target = NULL;
	}
	i = 0;
	if (newsize)
	{
		*target = (char *)malloc(newsize);
		if (*target)
		{
			while (i < newsize)
				(*target)[i++] = 0;
		}
	}
}
