/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwhite42 <FUCK THE NORM>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:32:13 by fwhite42          #+#    #+#             */
/*   Updated: 2024/01/16 15:45:28 by fwhite42         ###   ########.fr       */
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
}

int	main(int ac, char **av)
{
	int	fd;
	int	t;

	fd = open("./tests/test.txt", O_RDONLY);
	if (ac == 1)
		test(fd);
	else
	{
		t = atoi(av[1]);
		while (t--)
			test(fd);
	}
	return (1);
}
