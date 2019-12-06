/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:23:22 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/06 13:58:47 by skhalil       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# include <stdio.h> //delete before submission

int		get_next_line(int fd, char **line);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif