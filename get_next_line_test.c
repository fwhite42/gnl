/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:57:40 by fwhite42          #+#    #+#             */
/*   Updated: 2023/12/26 16:05:19 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<fcntl.h>
#include<stdio.h>

#include"get_next_line.h"

int	gnl_print(int fd)
{
	char	*line;

	line = get_next_line(fd);
	printf("LINE<%s>\n", line);
	return (!!line);
}

int	main(void)
{
	int		fd;
	char	*filename;
	char	*line;

	filename = TEST_NAME;
	fd = open(filename, O_RDONLY);
	while (gnl_print(fd))
		;
	return (0);
}
