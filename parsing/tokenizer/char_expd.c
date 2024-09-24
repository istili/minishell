/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_expd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:09:08 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/24 16:18:52 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	char_expdr(t_token **last, char *line, int i, t_link *envp)
{
	int		j;
	char	*data;

	if (ft_check(last) == 1)
	{
		(*last)->content[envp->j++] = line[i++];
		(*last)->content[envp->j] = '\0';
	}
	else
	{
		i++;
		j = i;
		while (line[i] && (is_alphnum(line[i])) == 0)
			i++;
		if (line[j - 1] == '$' && line[j] == '?')
			i++;
		data = ft_replace(line, j, i, envp);
		(*last)->exp = 1;
		if ((ft_strchr(data, ' ') || \
			ft_strchr(data, '\t'))	&& check_before(j, line) == 1)
			expd_space(data, last, envp);
		else if (ft_nrml_exp(data, envp, last) == -1)
			return (-1);
	}
	return (i);
}

int	ft_nrml_exp(char *data, t_link *envp, t_token **last)
{
	int	len;
	int	x;

	len = ft_strlen(data) + envp->len + envp->j + 3;
	(*last)->content = (char *)ft_realloc((*last)->content, len, envp->j);
	if (!(*last)->content)
		return (-1);
	x = 0;
	while (data[x])
		(*last)->content[envp->j++] = data[x++];
	(*last)->content[envp->j] = '\0';
	return (1);
}

static void	ft_helpernorms(char **split, t_token **last, t_link *envp)
{
	int	y;
	int	i;

	y = 1;
	i = 0;
	while (split[y])
	{
		(*last)->exp = y + 1;
		envp->tmp = lst_new(envp, ft_strlen(split[y]) + 1);
		to_next_node(last, envp->tmp);
		(*last) = ft_lstlast((*last));
		i = 0;
		while (split[y][i])
			(*last)->content[envp->j++] = split[y][i++];
		(*last)->content[envp->j] = '\0';
		y++;
	}
}

void	expd_space(char *data, t_token **last, t_link *envp)
{
	int		i;
	int		len;
	char	**split;

	i = 0;
	data = check_for_file(data);
	split = ft_split(data, ' ');
	if (!split[0])
		return ;
	len = ft_strlen(split[0]) + envp->j + 1;
	(*last)->content = (char *)ft_realloc((*last)->content, len, envp->j);
	while (split[0][i])
		(*last)->content[envp->j++] = split[0][i++];
	(*last)->content[envp->j] = '\0';
	ft_helpernorms(split, last, envp);
}

int	ft_check(t_token **last)
{
	if ((*last)->prev != NULL && ft_strcmp((*last)->prev->content, "<<") == 0)
		return (1);
	return (-1);
}
