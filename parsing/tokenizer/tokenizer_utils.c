/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:38:30 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/14 16:01:14 by hfiqar           ###   ########.fr       */
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
