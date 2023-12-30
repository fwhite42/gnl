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

typedef struct s_list
{
	void	*content;
	t_list	*next;
}				t_list;

typedef struct s_gnl_memory
{
	t_list	*cache;
	t_list	*garbage;
}				t_list;

typedef struct s_gnl_buffer
{
	int		fd;
	char	*data;
	size_t	offset;
	size_t	length;
	size_t	linelength;
}				t_gnl_buffer;

t_gnl_buffer	*gnl_write_cache(t_list *cache, int fd);
void			gnl_read_cache(t_list *cache, int fd);
void			gnl_delete_cache(t_list *cache, int fd);
void			gnl_collect_garbage(t_list garbage, t_gnl_buffer buff;
void			gnl_destroy_garbage(t_list *garbage);
void			gnl_recursion(int fd, t_gnl_memory *memory);
char			*get_next_line(int fd);
#endif 
