/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taquino- <taquino-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:26:24 by taquino-          #+#    #+#             */
/*   Updated: 2023/11/23 21:26:08 by taquino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct get_string
{
	char				*content;
	struct get_string	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*ft_lst_get_last(t_list *hidden);
int		found_newline(t_list *hidden);
int		ft_strlen(const char *str);
void	read_and_hidden(int fd, t_list **hidden);
void	add_to_hidden(t_list **hidden, char *buff, int readed);
void	extract_line(t_list *hidden, char **line);
void	clean_hidden(t_list **hidden);
void	generate_line(char **line, t_list *hidden);
void	free_hidden(t_list *hidden);
#endif