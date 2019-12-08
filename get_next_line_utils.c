/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: skhalil <skhalil@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:23:29 by skhalil        #+#    #+#                */
/*   Updated: 2019/12/08 13:48:16 by skhalil       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;
	size_t			i;

	dst_p = (unsigned char *)dst;
	src_p = (unsigned char *)src;
	i = 0;
	if (dst_p == NULL && src_p == NULL)
		return (dst);
	while (i < n)
	{
		dst_p[i] = src_p[i];
		i++;
	}
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = 0;
	if (dst)
	{
		while (src[srclen])
			srclen++;
		if (srclen + 1 < dstsize)
			ft_memcpy(dst, src, srclen + 1);
		else if (dstsize != 0)
		{
			ft_memcpy(dst, src, dstsize - 1);
			dst[dstsize - 1] = '\0';
		}
	}
	return (srclen);
}

size_t			ft_strnlen(char *s, size_t n)
{
	size_t i;

	i = 0;
	while (s[i] && i < n)
		i++;
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strnlen(dst, dstsize);
	if (dstsize < len)
		return (len + ft_strlen(src));
	return (len + ft_strlcpy(dst + len, src, dstsize - len));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	subslen;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if ((unsigned int)ft_strlen((char *)s) <= start)
		return (ft_calloc(1, 1));
	subslen = ft_strlen((char *)&s[start]);
	subslen = (subslen > len) ? len : subslen;
	subs = (char *)malloc(subslen + 1);
	if (subs == NULL)
		return (NULL);
	while (s[start + i] && subslen - i != 0)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

t_fd_buffer		*new_fd_buffer(int fd)
{
	t_fd_buffer		*ret;

	ret = (t_fd_buffer *)malloc(sizeof(t_fd_buffer));
	
	ret->fd_saved = (int *)malloc(sizeof(int));
	*(ret->fd_saved) = fd;

	ret->lb_index = (int *)malloc(sizeof(int));
	*(ret->lb_index) = 0;

	ret->linebuffer = NULL;
	ret->next = NULL;

	return (ret);
}