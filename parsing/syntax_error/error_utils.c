/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:52:46 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/14 14:53:46 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return (s1[i] - s2[i]);
}

bool	ft_red(t_token *token)
{
	if (token->type == REDIRECT_IN || \
	token->type == REDIRECT_OUT || \
	token->type == APPEND || \
	token->type == HEREDOC)
		return (true);
	return (false);
}
