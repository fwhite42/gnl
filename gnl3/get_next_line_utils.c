/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:34:24 by fwhite42          #+#    #+#             */
/*   Updated: 2024/01/01 15:06:30 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line"

t_list	*gnl_write_cache(t_gnl_memory *memory, int fd)
{
}

//==============================================================================
//	> gnl_read_cache
//
//	Inspects the memory->cache and returns the list node whose contnent is 
//	a buffer associated to the given fd.
//==============================================================================
t_list	*gnl_read_cache(t_gnl_memory *memory, int fd)
{
	t_list	*head;

	if (memory == NULL)
		return (NULL);
	head = memory->cache;
	while (head != NULL \
			&& ((t_gnl_buffer *)(head->content))->fd != fd)
	{
		head = head->next;
	}
	return (head);
}

void	gnl_delete_cache(t_gnl_memory *memory, int fd)
{
	t_list	*previous;
	t_list	*current;

	if (memory == NULL)
		return ;
	previous = NULL;
	current = memory->cache;
	while (current != NULL \
			&& ((t_gnl_buffer *)(current->content))->fd != fd)
	{
		previous = current;
		current = current->next;
	}
	previous->next = current->next;
	free(((t_gnl_buffer *)(current->content))->data);
	free(current->content);
	free(current);
}

void	gnl_collect_garbage(t_gnl_memory *memory, char *buff)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return ;
	node->content = (void *)buff;
	node->next = NULL;
	if (memory->garbage == NULL)
	{
	memory->garbage = node;
	}
	while (garbage->next != NULL)
		garbage = garbage->next;
	*garbage = node;
}

void	gnl_destroy_garbage(t_gnl_memory *memory)
{
	t_list	*head;
	size_t	i;

	i = 0;
	if (memory == NULL)
		return ;
	while (memory->garbage)
	{
		head = memory->garbage;
		memory->garbage = memory->garbage->next;
		while (i < BUFFER_SIZE)
			((char *)(head->content))[i++] = 0;
		free(head->content);
		head->content = NULL;
		head->next = NULL;
		free(head);
	}
}
