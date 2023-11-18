/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taquino- <taquino-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:26:24 by taquino-          #+#    #+#             */
/*   Updated: 2023/11/18 00:30:36 by taquino-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef get_next_line_h
#define get_next_line_h

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 50
#endif

#include <stdlib.h>
#include <stdio.h>

typedef struct get_string
{
    char    c;
    struct get_string *next;    
} node;












#endif