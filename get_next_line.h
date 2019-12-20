/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:23:22 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/20 18:23:06 by skhalil       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

void	empty_before_newline(char **r_buf);
int		read_to_rbuf_til_newline(int fd, char **r_buf);
void	read_from_buf(char **line, char *r_buf, int islast);
void	read_routine(char **line, char **r_buf, int *gnl_state, int islast);
int		get_next_line(int fd, char **line);
void	ft_strnjoin(char **s1, char *s2, int stopper);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_strlen(char *str);
int		newline_index(char *str);

#endif
