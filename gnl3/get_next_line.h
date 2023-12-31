/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:46:20 by fwhite42          #+#    #+#             */
/*   Updated: 2023/12/30 18:32:40 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
//list interface
typedef struct s_list
{
	void	*content;
	t_list	*next;
}	t_list;
//memory interface
typedef struct s_gnl_memory
{
	t_list	*cache;
	t_list	*garbage;
}	t_gnl_memory;
//buffer interface
typedef struct s_gnl_buffer
{
	int	fd;
	char	*data;
	size_t	offset;
	size_t	length;
}	t_gnl_buffer;
//=============================================================================
//	Cache nodes are list nodes with content pointing to a gnl_buffer
//	Utility functions for cache nodes:
//-----------------------------------------------------------------------------
//	>	Creates/over-write a cache node
t_gnl_buffer	*gnl_write_cache(t_list *cache, int fd);
//	>	Reads a cache node
t_gnl_buffer	*gnl_read_cache(t_list *cache, int fd);
//	>	Removes a cache node
int		gnl_delete_cache(t_list *cache, int fd);
//==============================================================================
//	Garbage nodes are list nodes with content pointing heap allocated memory
//	Utility functions for garbage nodes:
//------------------------------------------------------------------------------
//	>	Push a node to the list;
void		gnl_collect_garbage(t_list garbage, t_gnl_buffer buff;
//	>	Clear the garbage list;
int		gnl_destroy_garbage(t_list *garbage);
//==============================================================================
void		gnl_recursion(int fd, t_gnl_memory *memory);
char		*get_next_line(int fd);
#endif
