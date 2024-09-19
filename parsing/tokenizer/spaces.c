/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:52:03 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/19 00:19:47 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	spaces(t_token **token, char *line, int i, t_link *envp)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (1);
	if (after_space(token, line, i, envp) == -1)
		return (-1);
	return (1);
}

int	after_space(t_token **token, char *line, int i, t_link *envp)
{
	t_token	*tmp;

	tmp = lst_new(envp, ft_strlen(line) + 1);
	to_next_node(token, tmp);
	if (is_character(line[i]))
	{
		if (characters(token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_quote(line[i]) == 1)
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
		if (separator(token, line, i, envp) == -1)
			return (-1);
	}
	return (1);
}
