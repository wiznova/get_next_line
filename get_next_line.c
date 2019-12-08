/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:23:27 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/08 14:40:22 by skhalil       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

ssize_t	wline_from_linebuffer(t_fd_buffer *current, char **line)
{
	int		i;
	char	*temp;
	size_t	lb_len;

	lb_len = ft_strlen(current->linebuffer);
	i = 0;
	while (current->linebuffer[i])
	{
		if (current->linebuffer[i] == '\n')
		{
			if (*line != NULL)
				free(*line);
			*line = ft_substr(current->linebuffer, 0, i);
			temp = current->linebuffer;
			current->linebuffer = ft_substr(current->linebuffer, i + 1, lb_len);
			free(temp);
			return (1);
		}
		i++;
	}
	if (current->linebuffer[i] == '\0') //should it return last line?
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
	temp = NULL;
	ret_check = read(fd, read_buf, BUFFER_SIZE); //function that cats till newline?
	if (ret_check == -1 || ret_check == 0) //error or EOF
		return (ret_check);
	if (current->linebuffer == NULL)
		current->linebuffer = ft_substr(read_buf, 0, BUFFER_SIZE);
	else
	{
		temp = current->linebuffer;
		len = ft_strlen(current->linebuffer);
		current->linebuffer = (char *)calloc(len + BUFFER_SIZE + 1, 1);
		ft_strlcat(current->linebuffer, temp, len + BUFFER_SIZE + 1);
		ft_strlcat(current->linebuffer, read_buf, len + BUFFER_SIZE + 1);
	}
	free(temp);
	free(read_buf);
	return (ret_check);	
}

int		get_next_line(int fd, char **line)
{
	static t_fd_buffer	*fd_buffer_head;
	t_fd_buffer			*current;
	ssize_t				ret_check;

	ret_check = -1;	
	if (fd_buffer_head == NULL)
		fd_buffer_head = new_fd_buffer(fd);

	current = fd_buffer_head; //starting searching for fd from head
	while (*(current->fd_saved) != fd && current != NULL) //searching fd, list stays manually till freed
		current = current->next;
	if (current == NULL)
		current = new_fd_buffer(fd);
	while ((has_newline(&(current->linebuffer)) == 0 && ret_check != 0) || current->linebuffer == NULL) //check iff LB cane be returned NULL from read_next
		ret_check = read_next(fd, current); //check errors in read 0 or -1
	
	ret_check = wline_from_linebuffer(current, line);
	return (ret_check);
}
	
	
	
	// if (current->linebuffer == NULL)
	// 	ret_check = read_next(fd, current); //check errors in read