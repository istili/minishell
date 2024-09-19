/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:51:26 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/15 16:38:24 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_flag(t_token **last, char *line, int i)
{
	if (is_separator(line[i]))
		(*last)->flag = 1;
	else
		(*last)->flag = 0;
}

int	d_q_expdr(int i, t_token **last, char *line, t_link *envp)
{
	int		j;
	int		x;
	char	*data;
	int		len;

	if (ft_check(last) == 1)
		(*last)->content[envp->j++] = line[i++];
	else
	{
		i++;
		j = i;
		while (line[i] && (is_alphnum(line[i])) == 0)
			i++;
		if (line[j - 1] == '$' && line[j] == '?')
			i++;
		data = ft_replace(line, j, i, envp);
		len = ft_strlen(data) + envp->len + envp->j + 3;
		(*last)->content = (char *)ft_realloc((*last)->content, len, envp->j);
		if (!(*last)->content)
			return (-1);
		x = 0;
		while (data[x])
			(*last)->content[envp->j++] = data[x++];
	}
	return (i);
}

int	d_quote(t_token **token, char *line, int i, t_link *envp)
{
	t_token	*last;

	last = ft_lstlast(*token);
	i++;
	while (line[i] && is_quote(line[i]) != 2)
	{
		ft_flag(&last, line, i);
		if (line[i] == '$' && alpha(line[i + 1]) == 1)
			i = d_q_expdr(i, &last, line, envp);
		else if (line[i] == '$' && is_digit(line[i + 1]) == 1)
			i += 2;
		else
			last->content[envp->j++] = line[i++];
		last->content[envp->j] = '\0';
	}
	if (ft_writ(line[i]) == -1)
		return (-1);
	i++;
	last->quotes = 2;
	if (after_d_q(token, line, i, envp) == -1)
		return (-1);
	return (1);
}

int	ft_quotes(t_token **token, char *line, t_link *envp, int i)
{
	if ((is_quote(line[i]) == 1))
	{
		if (s_quote(token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_quote(line[i]) == 2)
	{
		if (d_quote(token, line, i, envp) == -1)
			return (-1);
	}
	return (1);
}

int	after_d_q(t_token **token, char *line, int i, t_link *envp)
{
	t_token	*tmp;

	if (is_quote(line[i]) != 0)
	{
		if (ft_quotes(token, line, envp, i) == -1)
			return (-1);
	}
	else if (is_separator(line[i]))
	{
		tmp = lst_new(envp, ft_strlen(line) + 1);
		to_next_node(token, tmp);
		if (separator(token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_space(line[i]))
	{
		if (spaces(token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_character(line[i]))
	{
		if (characters(token, line, i, envp) == -1)
			return (-1);
	}
	return (1);
}
