/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taquino- <taquino-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:26:24 by taquino-          #+#    #+#             */
/*   Updated: 2023/11/19 23:26:34 by taquino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef get_next_line_h
#define get_next_line_h

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 50
#endif

#include <stdlib.h>
#include <unistd.h>

typedef struct get_string
{
    char	*content;
    struct get_string	*next;    
} s_list;

char	*get_next_line(int fd);
void	read_and_hide(int fd, s_list **hidden);
void	add_to_hidden(s_list **hidden, char *buff, int readed);
void	extract_line(s_list *hidden, char **line);
void	clean_hidden(s_list **hidden);
int found_newline(s_list *hidden);
s_list  *ft_lst_get_last(s_list *hidden);
void    generate_line(char **line, s_list *hidden);
void	free_hidden(s_list *hidden);
int	ft_strlen(const char *str);


#endif