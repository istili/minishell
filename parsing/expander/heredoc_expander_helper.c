/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:19:01 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/13 00:13:07 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp(const	char	*s1, const	char	*s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin(char const *line, char const *bufr)
{
	char	*s;
	size_t	i;
	size_t	j;

	if (!bufr && !line)
		return (0);
	if (!bufr && line)
		return (ft_strdup(line));
	if (!line && bufr)
		return (ft_strdup(bufr));
	s = (char *)ft_malloc_gab(ft_strlen(line) + ft_strlen(bufr) + 1, 0);
	i = 0;
	while (line != NULL && line[i] != '\0')
	{
		s[i] = line[i];
		i++;
	}
	j = 0;
	while (bufr != 0 && bufr[j] != '\0')
	{
		s[i + j] = bufr[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
