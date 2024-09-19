/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 23:35:57 by istili            #+#    #+#             */
/*   Updated: 2024/09/13 21:50:17 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_value(char *s)
{
	int		i;
	int		j;
	int		k;
	char	*value;

	i = 0;
	while (s[i] && s[i] != '+' && s[i] != '=')
		i++;
	if (!s[i])
		return (NULL);
	if (s[i] == '+')
		i += 2;
	else if (s[i] == '=')
		i++;
	j = i;
	while (s[j])
		j++;
	value = ft_malloc_gab(j - i + 1, 0);
	k = 0;
	while (i < j)
		value[k++] = s[i++];
	value[k] = '\0';
	return (value);
}

static int	len(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '+' && s[i] != '=')
		i++;
	return (i);
}

int	check_arg(char *av)
{
	int		i;

	i = 0;
	if (is_alpha_(av[0]) == -1)
		return (1);
	while (av[i] && av[i] != '+' && av[i] != '=')
	{
		if (is_alphnum(av[i]) == -1)
			return (1);
		i++;
	}
	if ((av[i] == '+' && av[i + 1] == '=') || av[i] == '=' || !av[i])
		return (0);
	return (1);
}

char	*find_key(char *s, int *flag)
{
	int		i;
	int		j;
	char	*key;

	i = len(s);
	if (s[i] == '+')
		*flag = 1;
	key = ft_malloc_gab(i + 1, 0);
	j = -1;
	while (++j < i)
		key[j] = s[j];
	key[j] = '\0';
	return (key);
}
