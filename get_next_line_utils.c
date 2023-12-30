/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 16:06:35 by fwhite42          #+#    #+#             */
/*   Updated: 2023/12/29 16:40:24 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Copies linelen bytes from memory to dst
static void	gnl_memcpy(char *dst, char *memory, size_t linelen)
{
	while (linelen--)
		*(dst++) = *(memory++);
}

// Allocates a *buff and reads from fd, writing *buff.
static void	gnl_read(int fd, char **buff, ssize_t *bl)
{
	*buff = (char *)malloc(BUFFER_SIZE + 1);
	if (*buff && fd >= 0)
	{
		*bl = read(fd, *buff, BUFFER_SIZE);
	}
}

// Computes the length of a string in memory
static void	get_memory_length(char *memory, ssize_t *i)
{
	*i = 0;
	while (memory && memory[*i])
		(*i)++;
}

// Computes the length of a 'sep'-terminating string. If the string 0-terminates
// before reaching 'sep', the length of the string is returned, otherwise the
// length of the 'sep'-terminating string is returned ('sep' partecipates in
// length of the string)
static void	get_chunk_length(char *buff, size_t bl, char sep, size_t *cl)
{
	*cl = 0;
	while (*cl < bl && buff[*cl] != sep)
		(*cl)++;
	if (*cl < bl)
		(*cl)++;
}
