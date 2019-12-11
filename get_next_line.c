/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 19:10:45 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/11 20:42:23 by skhalil       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		newline_index(char *str) //returns index of newline in a string, or -1
{
	int		i;

	i = 0;
	if (str)
		while (str[i])
		{
			if (str[i] == '\n')
					return (i);
			i++;
		}
	return (-1);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	empty_before_newline(char **r_buf)
{
	char	*temp;
	int		r_buf_len;
	int		i;

	i = 0;
	r_buf_len = ft_strlen(*r_buf);
	if (r_buf_len - newline_index(*r_buf) >= 1)
	{
		temp = (char *)ft_calloc(r_buf_len - newline_index(*r_buf), 1); //that already should have place for nullterm
		if (temp == NULL)
			return ;
		while ((*r_buf)[i + newline_index(*r_buf) + 1])
		{
			temp[i] = (*r_buf)[i + newline_index(*r_buf) + 1];
			i++;
		}
		free(*r_buf);
		*r_buf = temp;
	}
	else
	{
		free(*r_buf);
		*r_buf = NULL;
	}
}

void	ft_strnjoin(char **s1, char *s2, int stopper) //joins whole s1 with upto s2[stopper - 1], stopper is an number of chars
{
	char	*joined_str;
	int		s1_len;
	int		i;

	i = 0;
	s1_len = 0;
	while ((*s1)[s1_len])
		s1_len++;
	joined_str = (char *)ft_calloc(s1_len + stopper + 1, 1);
	if (joined_str == NULL)
		return ;
	while ((*s1)[i])
	{
		joined_str[i] = (*s1)[i];
		i++;
	}
	while (i - s1_len < stopper)
	{
		joined_str[i] = s2[i - s1_len];
		i++;
	}
	free(*s1);
	*s1 = joined_str;
}

int		read_to_rbuf_til_newline(int fd, char **r_buf)
{
	char	*local_buf;
	int		read_ret;
	int		total_read;

	total_read = 0;
	local_buf = (char *)ft_calloc(BUFFER_SIZE, 1);
	if (local_buf == NULL)
		return (-1);
	if (local_buf == NULL)
		return (-1);
	while (newline_index(*r_buf) == -1)
	{
		read_ret = read(fd, local_buf, BUFFER_SIZE);
		if (read_ret < 0)
			return (read_ret);
		total_read += read_ret;
		if (read_ret == 0)
			return (-total_read);
		ft_strnjoin(r_buf, local_buf, read_ret);
	}
	free(local_buf);
	return (1); //means a newline is in r_buf
}

void	read_from_buf(char **line, char *r_buf, int islast)
{
	int		endline_i;

	endline_i = islast == 1 ? ft_strlen(r_buf) - 1 : newline_index(r_buf);
	if (islast != 1)
	{
		*line = (char *)ft_calloc((endline_i + 1) + 1, 1);
		if (*line == NULL)
			return ;
		while (endline_i > 0)
		{
			(*line)[endline_i - 1] = r_buf[endline_i - 1];
			endline_i--;
		}
	}
	else if (islast == 1)
	{
		*line = (char *)ft_calloc((endline_i + 1) + 1, 1);
		if (*line == NULL)
			return ;
		while (endline_i >= 0)
		{
			(*line)[endline_i] = r_buf[endline_i];
			endline_i--;
		}
	}
}

void	read_routine(char **line, char **r_buf, int *gnl_state, int islast)
{
		*gnl_state = islast == 1 ? 0 : 1;
		read_from_buf(line, *r_buf, islast); //for now islast is 0 when true
		if (islast == 0)
			empty_before_newline(r_buf);
		else if (islast == 1)
			free(*r_buf);
}

int		get_next_line(int fd, char **line)
{
	static char	*r_buf;
	int			gnl_state; // 1:line been read, 0:EOF reached, -1:error occured
	int			r_buf_size;

	gnl_state = -1;
	if (r_buf == NULL)
		r_buf = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (r_buf == NULL)
		return (-1);
	if (newline_index(r_buf) != -1)
		read_routine(line, &r_buf, &gnl_state, 0);
	else
	{
		r_buf_size = read_to_rbuf_til_newline(fd, &r_buf);
		if (r_buf_size > 0)
			read_routine(line, &r_buf, &gnl_state, 0);
		else if (r_buf_size <= 0)
			read_routine(line, &r_buf, &gnl_state, 1);
		else
			return (gnl_state);
	}
	return (gnl_state);
}
