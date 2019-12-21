/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 19:10:45 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/21 15:11:08 by skhalil       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		empty_before_newline(char **r_buf)
{
	char	*temp;
	int		r_buf_len;
	int		i;

	i = 0;
	r_buf_len = ft_strlen(*r_buf);
	if (r_buf_len - newline_index(*r_buf) >= 1)
	{
		temp = (char *)ft_calloc(r_buf_len - newline_index(*r_buf), 1);
		if (temp == NULL)
			return (-1);
		while ((*r_buf)[i + newline_index(*r_buf) + 1])
		{
			temp[i] = (*r_buf)[i + newline_index(*r_buf) + 1];
			i++;
		}
		free(*r_buf);
		*r_buf = temp;
	}
	return (1);
}

int		read_to_rbuf_til_newline(int fd, char **r_buf)
{
	char	*local_buf;
	int		read_ret;

	local_buf = (char *)ft_calloc(BUFFER_SIZE, 1);
	if (local_buf == NULL)
		return (-1);
	while (newline_index(*r_buf) == -1)
	{
		read_ret = read(fd, local_buf, BUFFER_SIZE);
		if (read_ret == -1 || read_ret == 0)
			return (read_ret);
		ft_strnjoin(r_buf, local_buf, read_ret);
	}
	free(local_buf);
	local_buf = NULL;
	return (1);
}

int		read_from_buf(char **line, char *r_buf, int islast)
{
	int		endline_i;

	endline_i = islast == 1 ? ft_strlen(r_buf) - 1 : newline_index(r_buf) - 1;
	*line = (char *)ft_calloc((endline_i + 1) + 1, 1);
	if (*line == NULL)
		return (-1);
	while (endline_i >= 0)
	{
		(*line)[endline_i] = r_buf[endline_i];
		endline_i--;
	}
	return (1);
}

int		read_routine(char **line, char **r_buf, int islast)
{
	if (read_from_buf(line, *r_buf, islast) == -1)
		return (-1);
	if (islast == 0)
	{
		if (empty_before_newline(r_buf) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*r_buf;
	int			gnl_state;

	gnl_state = -1;
	if (r_buf == NULL)
		r_buf = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (r_buf == NULL)
		return (on_error(&r_buf));
	if (newline_index(r_buf) != -1)
		gnl_state = read_routine(line, &r_buf, 0);
	else
	{
		gnl_state = read_to_rbuf_til_newline(fd, &r_buf);
		if (gnl_state != -1)
			gnl_state = read_routine(line, &r_buf, gnl_state == 1 ? 0 : 1);
	}
	if (gnl_state == -1)
		return (on_error(&r_buf));
	if (gnl_state == 0 && r_buf != NULL)
	{
		free(r_buf);
		r_buf = NULL;
	}
	return (gnl_state);
}
