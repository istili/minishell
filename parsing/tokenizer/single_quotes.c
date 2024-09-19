/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:46:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/15 10:55:28 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	s_quote(t_token **token, char *line, int i, t_link *envp)
{
	t_token	*last;

	last = ft_lstlast(*token);
	i++;
	last->quotes = 1;
	while (line[i] && is_quote(line[i]) != 1)
	{
		ft_flag(&last, line, i);
		last->content[envp->j++] = line[i++];
	}
	last->content[envp->j] = '\0';
	if (!line[i])
	{
		write(2, "unclosed single quotes\n", 23);
		exit_status(258, 1);
		return (-1);
	}
	else
		i++;
	if (after_s_q(token, line, i, envp) == -1)
		return (-1);
	return (1);
}

int	after_s_q(t_token **token, char *line, int i, t_link *envp)
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
