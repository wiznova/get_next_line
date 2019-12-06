/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:23:22 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/06 21:19:19 by skhalil       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h> //delete before submission
#define BUFFER_SIZE 10 //delete

typedef struct	 		s_fd_buffer
{
	int					*fd;
	int					*lb_index;
	char				*linebuffer;
	struct s_fd_buffer	*next;
}						t_fd_buffer;

int				get_next_line(int fd, char **line);
void			*ft_memcpy(void *dst, const void *src, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
t_fd_buffer		*new_fd_buffer(int fd);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);



#endif