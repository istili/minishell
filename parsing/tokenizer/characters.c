/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:41:35 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/14 18:18:47 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_before(int start, char *line)
{
	if (start < 2)
		return (1);
	start = start - 2;
	while (line[start] == ' ' || line[start] == '\t')
		start--;
	if (line[start] == '<' || line[start] == '>' || line[start] == '=')
		return (-1);
	return (1);
}

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (-1);
}

int	alpha(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_' || c == '?')
		return (1);
	return (-1);
}

int	characters(t_token **token, char *line, int i, t_link *envp)
{
	t_token	*last;

	last = ft_lstlast(*token);
	while (line[i] && is_character(line[i]))
	{
		if (line[i] == '$' && alpha(line[i + 1]) == 1)
			i = char_expdr(&last, line, i, envp);
		else
		{
			if (line[i] == '$' && is_digit(line[i + 1]) == 1)
				i += 2;
			else if (line[i] == '$' && is_quote(line[i + 1]) != 0)
				i++;
			else
				last->content[envp->j++] = line[i++];
			last->content[envp->j] = '\0';
		}
	}
	if (!line[i])
		return (1);
	if (after_char(token, line, i, envp) == -1)
		return (-1);
	return (1);
}

int	after_char(t_token **token, char *line, int i, t_link *envp)
{
	t_token	*tmp;

	if (is_quote(line[i]) == 1)
	{
		if (s_quote(token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_quote(line[i]) == 2)
	{
		if (d_quote(token, line, i, envp) == -1)
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
	return (1);
}
