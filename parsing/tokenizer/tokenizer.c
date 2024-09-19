/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:54:07 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/15 11:31:50 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_token(t_token **token, char *line, t_link *envp, int i)
{
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
		if (separator(token, line, i, envp) == -1)
			return (-1);
	}
	else if (is_character(line[i]))
	{
		if (characters(token, line, i, envp) == -1)
			return (-1);
	}
	return (1);
}

void	ft_exp(t_token *tok)
{
	while (tok)
	{
		if (tok->exp < 1)
			tok->exp = 0;
		tok = tok->next;
	}
}

t_token	*ft_tokenizer(char *line, t_link *envp)
{
	t_token	*data;
	t_token	*token;
	int		i;

	envp->len = ft_strlen(line);
	data = NULL;
	token = NULL;
	i = 0;
	if (is_space(line[i]))
	{
		if (spaces(&token, line, i, envp) == -1)
			return (NULL);
	}
	else
	{
		data = lst_new(envp, envp->len);
		to_next_node(&token, data);
		if (ft_token(&token, line, envp, i) == -1)
			return (NULL);
	}
	ft_exp(token);
	return (token);
}
