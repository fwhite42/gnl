/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:35:47 by fwhite42          #+#    #+#             */
/*   Updated: 2023/12/30 18:32:47 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*get_next_line(int fd)
{
	char	*line;
	static t_gnl_memory memory;

	line = NULL;
	gnl_recursion(fd, &line, &memory);
	gnl_destroy_garbage(memory.garbage);
	return *line;
}
