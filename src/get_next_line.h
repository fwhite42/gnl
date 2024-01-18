/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:36:42 by fwhite42          #+#    #+#             */
/*   Updated: 2024/01/17 12:52:21 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<stdlib.h>
# include<unistd.h>
# include<stdio.h>
//============================================================================//
//	> Prototype:
char	*get_next_line(int fd);
//	> Defined in:
//		get_next_line.c
//	> Description:
//		Returns the next readable line from fd. If an error occurs it returns
//		NULL.
//============================================================================//
//	> Prototype :
void	gnl_memory_copy(char *dst, char *src, size_t len);
//	> Defined in:
//		get_next_line_utils.c
//	> Description
//		If either dst or src are NULL, nothing happens.
//		If both dst and src point to some char, the value of dst[i] is set to
//		src[i] for i = 0, ..., len - 1.
//============================================================================//
//	> Prototype:
char	gnl_is_separator(char *sep_list, int sep_list_length, char x);
//	> File:
//		get_next_line_utils.c
//	> Description:
//		Checks if x is equal to sep_list[i] for some value of i inside
//		{0, ..., sep_list_length - 1}
//============================================================================//
//	> Prototype :
void	gnl_bzero(char *target, size_t len);
//	> Defined in:
//		get_next_line_utils.c
//	> Description
//		If target is not NULL, target[i] is set to 0 for values of i ranging 
//		from 0 to len - 1 (included).
//============================================================================//
//	> Prototype:
size_t	gnl_memory_len(char *char_ptr, char *sep_list, int sep_list_length);
//	> Defined in:
//		get_next_line_utils.c
//	> Description:
//		Computes the length of a SEP-terminating string, where SEP is any
//	    character in sep_list (which is not necessarly a '\0'-terminating
//	    string, hence the presence of sep_list_length).
//============================================================================//
//	> Prototype:
void	gnl_config_memory(char **target, size_t oldsize, size_t newsize);
//	> Defined in:
//		get_next_line_utils.c
//	> Description :
//		If *target is not NULL, *target is freed and set to NULL.
//		If old_size is not 0 (before freeing the *target) the value of
//		*target[i] is set to zero (for i = 0,..., old_size - 1).
//		If new_size is not 0, the value of *target is set to some pointer
//		returned by a call to malloc(new_size)
//============================================================================//
//	> Prototype:
int		gnl_read_and_append(int fd, char **cache);
//	> Defined in:
//		get_next_line.c
//	> Description:
//		The first thing this function does is to read from the fd, into a
//		buffer (of BUFFER_SIZE).
//		If no bytes are read, the function returns 0.
//		If a reading error occurs, the function returns a negative number.
//		If data was read from the fd, the value of *cache is updated as
//		follows:
//		a. The current *cache length  is computed
//		b. A new_cache pointer is allocated, reserving enougth memory to store
//		   both the current cache and the new buffer.
//		c. Data from the old *cache is copied to the new_cache, and the buffer
//		   is also copied to the new_cache.
//		d. Then the old *cache is zeroed, freed, and then its value is updated
//		   with the address of the new_cache.
//============================================================================//
//	> Prototype:
int		gnl_split_cache_and_send2memory(char **cache, char **memory);
//	> Defined in:
//		get_next_line.c
//	> Description:
//		The data stored in cache is split, in a way to extract the first line
//		stored in *cache.
//		If a line is indeed found:
//		1. a new string with copy of the line is created;
//		2. a new string with a copy of the remaining chunk of the cache
//		  is created;
//		3. *cache is freed, zeroed and updated to the address of the string
//		  with the line
//		4. *memory is set to the address of the string with the remaining
//			chunks
//		* More precisely:
//		The total length of the string stored at *cache as well as the length
//		of the first line stored at *cache is computed.
//		If these two lengths coincide, no new line character was found in the
//		*cache.
//		If these length are different, a new line character was found in the
//		*cache, and their difference of defines the length of the new memory.
//============================================================================//
#endif
