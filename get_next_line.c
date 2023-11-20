/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taquino- <taquino-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:24:36 by taquino-          #+#    #+#             */
/*   Updated: 2023/11/20 00:22:20 by taquino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static s_list	*hidden;
	char			*line;

	hidden = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	// 1. read from fd and add to linked list;
	read_and_hide(fd, &hidden);
	if (hidden == NULL)
		return NULL;
	// 2. extract from hiding to line;
	extract_line(hidden, &line);
	// 3. clean up hidden;
	clean_hidden(&hidden);	
	if (line[0] == '\0')
	{
		free_hidden(hidden);
		hidden = NULL;
		free (line);
		return (NULL);
	}
	return (line);
}

// Uses read() to add characters to the hiding;
void	read_and_hide(int fd, s_list **hidden)
{
	char	*buff;
	int	readed;
	
	readed = 1;
	while (!found_newline(*hidden) && readed != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return;
		readed = (int)read(fd, buff, BUFFER_SIZE);
		if ((*hidden == NULL && readed == 0) || readed == -1)
		{
			free(buff);
			return;
		}		
		buff[readed] = '\0';
		add_to_hidden(hidden, buff, readed);
		free(buff);
	}
}
// Adds the content of our buffer to the end of our hiding.
void	add_to_hidden(s_list **hidden, char *buff, int readed)
{
	int	i;
	s_list	*last;
	s_list	*new_node;

	new_node = malloc(sizeof(s_list));
	if (new_node == NULL)
		return;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (readed + 1));
	if (new_node->content == NULL)
		return;
	i = 0;
	while (buff[i] && i < readed)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*hidden == NULL)
	{
		*hidden = new_node;
		return;
	}
	last = ft_lst_get_last(*hidden);
	last->next = new_node;
}
/* 
	Extracts all characters from our hidden and stores then it out line
	stopping after the first \n founded.
*/
void	extract_line(s_list *hidden, char **line)
{
	int	i;
	int	j;

	if (hidden == NULL)
		return;
	generate_line(line, hidden);
	if (*line == NULL)
		return;
	j = 0;	
	while (hidden)
	{
		i = 0;
		while (hidden->content[i])
		{
			if (hidden->content[i] == '\n')
			{
				(*line)[j++] = hidden->content[i];
				break;
			}
			(*line)[j++] = hidden->content[i++];
		}
		hidden = hidden->next;
	}
	(*line)[j] = '\0';
}
/*
	After extracting the line that was read, we don't need those characters anymore.
	This function clears the hiding so only the char that have not been returned at
	the end of GNL() remain in our static hiding.
*/
void	clean_hidden(s_list **hidden)
{
	s_list	*last;
	s_list	*clean_node;
	int	i;
	int	j;

	clean_node = malloc(sizeof(s_list));
	if (hidden == NULL || clean_node == NULL)
		return;
	clean_node->next = NULL;
	last = ft_lst_get_last(*hidden);
	i = 0;	
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (clean_node->content == NULL)
		return;
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