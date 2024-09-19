/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:53:08 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/14 15:59:03 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	separator(t_token **token, char *line, int i, t_link *envp)
{
	t_token	*last;

	last = ft_lstlast(*token);
	while (line[i] && is_separator(line[i]))
		last->content[envp->j++] = line[i++];
	last->content[envp->j] = '\0';
	last->flag = 0;
	if (!line[i])
		return (1);
	if (after_separ(token, line, i, envp) == -1)
		return (-1);
	return (1);
}

int	after_separ(t_token **token, char *line, int i, t_link *envp)
{
	t_token	*tmp;

	if (is_space(line[i]))
	{
		if (spaces(token, line, i, envp) == -1)
			return (-1);
	}
	else
	{
		tmp = lst_new(envp, ft_strlen(line) + 1);
		to_next_node(token, tmp);
		if (is_quote(line[i]) != 0)
		{
			if (ft_quotes(token, line, envp, i) == -1)
				return (-1);
		}
		else if (is_character(line[i]))
		{
			if (characters(token, line, i, envp) == -1)
				return (-1);
		}
	}
	return (1);
}
