/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:23:22 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/08 17:27:45 by skhalil       ########   odam.nl         */
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
	int					*fd_saved;
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

int		read_to_rbuf_til_newline(int fd, char *r_buf);
void	ft_strnjoin(char *s1, char *s2, int	stopper);
void	empty_before_newline(char *r_buf);
int		newline_index(char *str);


#endif