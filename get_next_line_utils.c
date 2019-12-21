/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:23:29 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/21 15:31:57 by skhalil       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** returns index of a newline in a string or -1
*/

int		newline_index(char *str)
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

int		free_buf(char **r_buf, int ret)
{
	if (*r_buf != NULL)
	{
		free(*r_buf);
		*r_buf = NULL;
	}
	return (ret);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = (void *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	if (count * size != 0)
	{
		str = (char *)ptr;
		while (i < count * size)
		{
			str[i] = '\0';
			i++;
		}
	}
	return (ptr);
}

/*
** joins whole s1 with upto s2[stopper - 1], stopper is an number of chars
*/

int		ft_strnjoin(char **s1, char *s2, int stopper)
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
		return (-1);
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
	return (0);
}
