/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:46:20 by fwhite42          #+#    #+#             */
/*   Updated: 2023/12/31 16:40:38 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
//==============================================================================
//	Three structures/objects are defined:
//	> list
//	> buffer
//	> memory
//==============================================================================
typedef struct s_list
{
	void	*content;
	t_list	*next;
}	t_list;

typedef struct s_gnl_buffer
{
	int		fd;
	char	*data;
	size_t	offset;
	size_t	length;
}	t_gnl_buffer;

typedef struct s_gnl_memory
{
	t_list	*cache;
	t_list	*garbage;
}	t_gnl_memory;

//==============================================================================
//	Cache nodes are list nodes with content pointing gnl_buffers
//	Utility functions for cache nodes are used to
//==============================================================================
//	> 1			create/override a cache node
t_gnl_buffer	*gnl_write_cache(t_list *cache, int fd);
//	> 2			read a cache node
t_gnl_buffer	*gnl_read_cache(t_list *cache, int fd);
//	> 3			remove a cache node
int				gnl_delete_cache(t_list *cache, int fd);

//==============================================================================
//	Garbage nodes are list nodes with content pointing heap allocated memory
//	Utility functions for garbage nodes are used to
//==============================================================================
//	> 4			push a node to the list
void			gnl_collect_garbage(t_list garbage, t_gnl_buffer buff);
//	> 5			clear the garbage list and free anything inside it
int				gnl_destroy_garbage(t_list *garbage);

//==============================================================================
//
//==============================================================================
//	> 6
size_t			gnl_get_chunk_length(t_gnl_buffer *buff);
//	> 7
void			gnl_memory_copy(char *dst, char *src, size_t len);
//	> 8
void			gnl_recursion(int fd, t_gnl_memory *memory);
char			*get_next_line(int fd);
#endif
