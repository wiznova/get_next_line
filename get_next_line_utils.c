/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:23:29 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/11 21:20:44 by skhalil       ########   odam.nl         */
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

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	if (n != 0)
	{
		str = (char *)s;
		while (i != n)
		{
			str[i] = '\0';
			i++;
		}
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/*
** joins whole s1 with upto s2[stopper - 1], stopper is an number of chars
*/

void	ft_strnjoin(char **s1, char *s2, int stopper)
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
