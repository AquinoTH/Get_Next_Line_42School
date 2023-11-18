/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taquino- <taquino-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:24:36 by taquino-          #+#    #+#             */
/*   Updated: 2023/11/17 23:34:55 by taquino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*get_next_line(int fd)
{
	
	if (fd < 0)
		return (NULL);
	
	





		
	return ;
}

int	main()
{
	int	fd;
	char	*buff;

	fd = open("file01.txt", O_RDONLY);
	while (1)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break;
		printf("%s\n", buff);
		free(buff);
	}
	return (0);
}	