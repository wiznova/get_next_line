/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:23:27 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/06 13:58:13 by skhalil       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 10

int     get_next_line(int fd, char **line)
{
    ssize_t     read_ret;
    void        *buf;

    buf = (void *)malloc(BUFFER_SIZE);
    *line = (char *)malloc(BUFFER_SIZE);
    read_ret = read(fd, buf, BUFFER_SIZE);
    ft_memcpy(*line, buf, BUFFER_SIZE - 1);
    (*line)[BUFFER_SIZE - 1] = '\0'; //testing what's inside buffer
    printf("%s\n", (char *)buf); //delete
    return (0);
}
