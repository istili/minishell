/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:58:51 by istili            #+#    #+#             */
/*   Updated: 2024/09/13 21:49:26 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alpha_(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_')
		return (0);
	return (-1);
}

int	is_alphnum(char c)
{
	if (is_alpha_(c) != -1 || (c >= '0' && c <= '9'))
		return (0);
	return (-1);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	x;
	size_t	slen;

	x = 0;
	slen = ft_strlen(src);
	if (dstsize != 0)
	{
		while (src[x] && x < (dstsize - 1))
		{
			dst[x] = src[x];
			x++;
		}
		dst[x] = 0;
	}
	return (slen);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		sub = ft_malloc_gab(1, 0);
		sub[0] = '\0';
		return (sub);
	}
	if (len > slen - start)
		len = (slen - start);
	sub = ft_malloc_gab(len + 1, 0);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
