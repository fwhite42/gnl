/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:32:13 by fwhite42          #+#    #+#             */
/*   Updated: 2024/01/02 22:51:11 by fwhite42         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"
#include <fcntl.h>
#include<stdio.h>

void	test(int fd)
{
	char	*line;

	line = get_next_line(fd);
	printf("%s\033[41m \033[0m", line);
	printf("////////////////////////////////////////\n");
}

int	main(void)
{
	int	fd;

	fd = open("test", O_RDONLY);
	test(fd);
	return (1);
}
