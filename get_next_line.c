#include "get_next_line.h"



int		newline_index(char *str) //returns index of newline in a string, or -1
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			 return (i);
		i++;
	}
	return (-1);
}

void	empty_before_newline(char **r_buf)
{
	char	*temp;
	int		r_buf_len;
	int		i;

	i = 0;
	r_buf_len = 0;
	while ((*r_buf)[r_buf_len])
		r_buf_len++;
	temp = (char *)calloc(r_buf_len - newline_index(*r_buf), 1); //that already should have place for nullterm
	while ((*r_buf)[i + newline_index(*r_buf)])
	{
		temp[i] = (*r_buf)[i + newline_index(*r_buf) + 1];
		i++;
	}
	temp[r_buf_len - newline_index(*r_buf)] = '\0';
	free(*r_buf);
	*r_buf = temp;
	temp = NULL;
}

void	ft_strnjoin(char **s1, char *s2, int stopper) //joins whole s1 with upto s2[stopper - 1], stopper is an number of chars
{
	char	*joined_str;
	int		s1_len;
	int		i;

	i = 0;
	s1_len = 0;
	if ((*s1) && s2)
	{
		while ((*s1)[s1_len])
			s1_len++;
		joined_str = (char *)calloc(s1_len + stopper + 1, 1);
		while ((*s1)[i] && i < s1_len)
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
}

int		read_to_rbuf_til_newline(int fd, char **r_buf)
{
	char	*local_buf;
	int		read_ret;

	local_buf = (char *)calloc(BUFFER_SIZE, 1);
	while (newline_index(*r_buf) == -1)
	{
		read_ret = read(fd, local_buf, BUFFER_SIZE);
		if (read_ret <= 0)
			return (read_ret);
		ft_strnjoin(r_buf, local_buf, read_ret);
	}
	free(local_buf);
	return (1); //means a newline is in r_buf
}

void	read_from_buf(char **line, char *r_buf)
{
	int		nl_i;
	int		i;

	i = 0;
	nl_i = newline_index(r_buf);
	*line = (char *)calloc((nl_i + 1) + 1, 1);
	while (i < nl_i)
	{
		(*line)[i] = r_buf[i];
		i++;
	}
	(*line)[i] = '\n';
}

int		get_next_line(int fd, char **line)
{
	static char	*r_buf;
	int			gnl_state; // 1:line been read, 0:EOF reached, -1:error occured

	gnl_state = -1;
	if (r_buf == NULL)
		r_buf = (char *)calloc(BUFFER_SIZE + 1, 1);

	if (newline_index(r_buf) != -1)
	{
		gnl_state = 1;
		read_from_buf(line, r_buf);
		empty_before_newline(&r_buf);
	}
	else
	{
		gnl_state = read_to_rbuf_til_newline(fd, &r_buf);
		if (gnl_state == 1)
		{
			read_from_buf(line, r_buf);
			empty_before_newline(&r_buf);
		}
		else
			return (gnl_state);
	}
	return (gnl_state);
}