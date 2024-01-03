/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:36:42 by fwhite42          #+#    #+#             */
/*   Updated: 2024/01/03 13:52:35 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<stdlib.h>
# include<unistd.h>
# include<stdio.h>
# define BUFFER_SIZE 42

//============================================================================//
//============================================================================//
void	gnl_memory_copy(char *dst, char *src, size_t len);
//============================================================================//
//============================================================================//
char	gnl_is_separator(char *sep_list, int sep_list_length, char x);
size_t	gnl_memory_len(char *char_ptr, char *sep_list, int sep_list_length);
//============================================================================//
//============================================================================//
void	gnl_malloc(char **target, size_t oldsize, size_t newsize);
//============================================================================//
//============================================================================//
int		gnl_read_and_append(int fd, char **data);
//============================================================================//
//============================================================================//
int		gnl_split(char **data, char **memory);
//============================================================================//
//============================================================================//
char	*get_next_line(int fd);

#endif
