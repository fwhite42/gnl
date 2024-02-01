/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                                  4 2              */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:32:13 by fwhite42          #+#    #+#             */
/*   Updated: 2024/02/01 14:16:56 by fwhite42           _)/_\---/_\(_         */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"
#include <fcntl.h>
#include<stdio.h>

void	test(int fd)
{
	char	*line;

	line = get_next_line(fd);
	printf(">>>>> %s\033[41m \033[0m", line);
}

int	main(int ac, char **av)
{
	int	fd;
	int	t;

	int fd1;
	int fd2;
	int fd3;
	int fd4;
	int fd5;
	int fd6;

	fd = open("./tests/test.txt", O_RDONLY);
	if (ac == 1)
		test(fd);
	else
	{
		t = atoi(av[1]);
		while (t--)
		{
			test(fd);
		}
	}
	return (1);
}
