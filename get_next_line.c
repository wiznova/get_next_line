/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:23:27 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/06 22:00:32 by skhalil       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	wline_from_linebuffer(t_fd_buffer *current, char **line)
{
	int		i;
	char	*temp;
	size_t	end;

	end = ft_strlen(current->linebuffer);
	i = *(current->lb_index);
	while (current->linebuffer[i])
	{
		if (current->linebuffer[i] == '\n')
		{
			if (*line != NULL)
				free(*line);
			*line = ft_substr(current->linebuffer, *(current->lb_index), i - *(current->lb_index));
			*(current->lb_index) = 0; //not actually necessary if realloc the linebuf
			temp = current->linebuffer;
			current->linebuffer = ft_substr(current->linebuffer, i + 1, end);
			free(temp);
			return (1);
		}
		i++;
	}
	if (current->linebuffer[i] == '\0')
		return (0);
	return (-1);
}

ssize_t	read_next(int fd, t_fd_buffer *current)
{
	void	*read_buf;
	char	*temp;
	ssize_t	ret_check;
	size_t	len;

	read_buf = (void *)malloc(BUFFER_SIZE);
	ret_check = read(fd, read_buf, BUFFER_SIZE); //function that cats till newline?
	if (ret_check == -1 || ret_check == 0) //error or EOF
		return (ret_check);
	if (current->linebuffer == NULL)
		current->linebuffer = ft_substr(read_buf, 0, BUFFER_SIZE);
	else
	{
		temp = current->linebuffer;
		len = ft_strlen(&(current->linebuffer[*(current->lb_index)]));
		current->linebuffer = (char *)malloc(len + BUFFER_SIZE + 1);
		ft_strlcat(current->linebuffer, temp, len + BUFFER_SIZE + 1);
		ft_strlcat(current->linebuffer, read_buf, len + BUFFER_SIZE + 1);
		free(temp);
	}
	*(current->lb_index) = 0;
	free(read_buf);
	return (ret_check);	
}

int		has_newline(char **str)
{
	int	i;

	i = 0;
	if ((*str) == NULL)
		return (-1);
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_fd_buffer	*fd_buffer;
	t_fd_buffer			*current;
	ssize_t				ret_check;

	ret_check = -10;	
	if (fd_buffer == NULL)
		fd_buffer = new_fd_buffer(fd);

	current = fd_buffer; //starting searching for fd from head
	while (*(current->fd) != fd && current != NULL) //searching fd, list stays manually till freed
		current = current->next;
	if (current == NULL)
	{
		current = new_fd_buffer(fd);
		ret_check = read_next(fd, current); //check errors in read
	}
	if (current->linebuffer == NULL)
		ret_check = read_next(fd, current); //check errors in read
	while (has_newline(&(current->linebuffer)) == 0 && ret_check != 0)
	{
		ret_check = read_next(fd, current); //check errors in read
	}
	ret_check = wline_from_linebuffer(current, line);
	if (ret_check == 1)
		return (1);

	return (0);
}