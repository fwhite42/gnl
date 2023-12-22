/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:28:50 by fwhite42          #+#    #+#             */
/*   Updated: 2023/12/22 18:18:40 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 42

static char	*gnl_main(size_t offset, int fd, char **dst, char **memory)
{
	size_t	linelen;
	size_t	memlen;

	memlen = 0;
	while ((*memory)[memlen])
		memlen++;
	if (memlen == 0)
	{
		if (*memory != NULL)
			free(*memory - BUFFER_SIZE);
		*memory = (char *)malloc(BUFFER_SIZE + 1);
		read(fd, memory, BUFFER_SIZE);
		memory[BUFFER_SIZE] = 0;
		memlen = BUFFER_SIZE;
	}
	while (linelen < memlen && (*memory)[linelen] != '\n')
		linelen++;
	if (!dst && linelen < memlen)
		dst = malloc(offset + linelen);
	else
		gnl_main(dst, offset + linelen, fd, memory + linelen);
	while (linelen--)
		*dst++ = *memory++;
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*dst;

	dst = NULL;
	memory = NULL;
	gnl_main(0, fd, &dst, &memory);
	return (dst);
}
