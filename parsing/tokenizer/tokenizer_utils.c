/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:38:30 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/22 20:51:15 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_quote(int c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else
		return (0);
}

bool	is_separator(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool	is_character(int c)
{
	if (!(is_quote(c)) && !(is_separator(c)) && !(is_space(c)))
		return (true);
	return (false);
}

int	full_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s, " ") || !ft_strcmp(s, "\t"))
			i++;
		else
			return (0);
	}
	return (1);
}
