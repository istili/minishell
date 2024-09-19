/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:23:40 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/14 14:19:53 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token_type	ft_error(void)
{
	write(2, "my_bash: syntax error near unexpected token\n", 44);
	exit_status(258, 1);
	return (none);
}

bool	ft_si(t_token *token)
{
	if (!token)
		return (0);
	if (token_content_type(token) == REDIRECT_IN || \
	token_content_type(token) == REDIRECT_OUT || \
	token_content_type(token) == APPEND)
		return (1);
	return (0);
}
