/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:01:26 by istili            #+#    #+#             */
/*   Updated: 2024/07/31 12:17:04 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error(char *s)
{
	if (s)
		write(2, s, ft_strlen(s));
	ft_malloc_gab(0, 1);
	exit(1);
}

static size_t	ft_word(char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			j++;
			i++;
		}
		if (j > 0)
		{
			k++;
			j = 0;
		}
	}
	return (k);
}

static size_t	ft_count(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char *s, char c)
{
	char	**str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	str = ft_malloc_gab((ft_word(s, c) + 1) * sizeof(char *), 0);
	i = 0;
	j = 0;
	while (i < ft_word(s, c))
	{
		while (s[j] && s[j] == c)
			j++;
		str[i] = ft_substr(s, j, ft_count((&s[j]), c));
		i++;
		j += ft_count((s + j), c);
	}
	str[i] = 0;
	return (str);
}
