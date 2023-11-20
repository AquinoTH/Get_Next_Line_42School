/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taquino- <taquino-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:25:56 by taquino-          #+#    #+#             */
/*   Updated: 2023/11/20 00:21:40 by taquino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


// Looks for a newline char in the given linked list.

int found_newline(s_list *hidden)
{
    int     i;
    s_list *current;

    if (hidden == NULL)
        return (0);
    current = ft_lst_get_last(hidden);
    i = 0;
    while (current->content[i])
    {
        if(current->content[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

// Returns a pointer to the last node in our hidden.

s_list  *ft_lst_get_last(s_list *hidden)
{
    s_list  *current;

    current = hidden;
    while (current && current->next)
        current = current->next;
    return (current);
}

/*
    Calculates the number of chars in the current line
    including the trailing \n if there's one, and allocates mem appropriately.
*/

void    generate_line(char **line, s_list *hidden)
{
    int i;
    int len;

    len = 0;
    while (hidden)
    {
    	i = 0;
        while (hidden->content[i])
        {
            if (hidden->content[i] == '\n')
            {
                len++;
                break;
            }
            len++;
            i++;
        }
        hidden = hidden->next;
    }
    *line = malloc(sizeof(char) * (len + 1));
}

// Frees the entire hidden

void	free_hidden(s_list *hidden)
{
	s_list	*current;
	s_list	*next;

	current = hidden;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}