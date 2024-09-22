/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:01:26 by istili            #+#    #+#             */
/*   Updated: 2024/09/22 21:00:23 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error(char *s, t_cmds *cmd)
{
	if (s)
		write(2, s, ft_strlen(s));
	if (cmd)
		close_fd(cmd);
	ft_malloc_gab(0, 1);
	exit(1);
}

static size_t	ft_word(char *s, char c, char c1)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		j = 0;
		while ((s[i] == c || s[i] == c1) && s[i])
			i++;
		while ((s[i] != c || s[i] != c1) && s[i])
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

static size_t	ft_count(char *s, char c, char c1)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != c || s[i] != c1))
		i++;
	return (i);
}

char	**ft_split(char *s, char c, char c1)
{
	char	**str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	str = ft_malloc_gab((ft_word(s, c, c1) + 1) * sizeof(char *), 0);
	i = 0;
	j = 0;
	while (i < ft_word(s, c, c1))
	{
		while (s[j] && (s[j] == c || s[j] == c1))
			j++;
		str[i] = ft_substr(s, j, ft_count((&s[j]), c, c1));
		i++;
		j += ft_count((s + j), c, c1);
	}
	str[i] = 0;
	return (str);
}
