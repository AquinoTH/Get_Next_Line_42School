/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taquino- <taquino-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:24:36 by taquino-          #+#    #+#             */
/*   Updated: 2023/11/23 21:29:16 by taquino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*hidden = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	read_and_hidden(fd, &hidden);
	if (hidden == NULL)
		return (NULL);
	extract_line(hidden, &line);
	clean_hidden(&hidden);
	if (line[0] == '\0')
	{
		free_hidden(hidden);
		hidden = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

/* Uses read() to add characters to the hidden */

void	read_and_hidden(int fd, t_list **hidden)
{
	char	*buf;
	int		readed;

	readed = 1;
	while (!found_newline(*hidden) && readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		readed = (int)read(fd, buf, BUFFER_SIZE);
		if ((*hidden == NULL && readed == 0) || readed == -1)
		{
			free(buf);
			return ;
		}
		buf[readed] = '\0';
		add_to_hidden(hidden, buf, readed);
		free(buf);
	}
}

/* Adds the content of our buffer to the end of our hidden */

void	add_to_hidden(t_list **hidden, char *buf, int readed)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (readed + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buf[i] && i < readed)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*hidden == NULL)
	{
		*hidden = new_node;
		return ;
	}
	last = ft_lst_get_last(*hidden);
	last->next = new_node;
}

/* Extracts all characters from our hidden and stores them in out line.
 * stopping after the first \n it encounters */

void	extract_line(t_list *hidden, char **line)
{
	int	i;
	int	j;

	if (hidden == NULL)
		return ;
	generate_line(line, hidden);
	if (*line == NULL)
		return ;
	j = 0;
	while (hidden)
	{
		i = 0;
		while (hidden->content[i])
		{
			if (hidden->content[i] == '\n')
			{
				(*line)[j++] = hidden->content[i];
				break ;
			}
			(*line)[j++] = hidden->content[i++];
		}
		hidden = hidden->next;
	}
	(*line)[j] = '\0';
}

void	clean_hidden(t_list **hidden)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (hidden == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*hidden);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(
			sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_hidden(*hidden);
	*hidden = clean_node;
}

/*
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int	fd;
	char	*buff;

	fd = open("file01.txt", O_RDONLY);
	while (1)
	{
		buff = get_next_line(fd);
		printf("%s", buff);
		if (buff == NULL)	
			break;
		free(buff);
	}
	return (0);
}	
*/
