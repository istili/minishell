/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:43:24 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/23 22:22:31 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_pipe(void)
{
	write(2, "my_bash: syntax error near unexpected token `|'\n", 48);
	exit_status(258, 1);
}

void	error_red(void)
{
	write(2, "my_bash: syntax error near unexpected token `newline'\n", 54);
	exit_status(258, 1);
}

void	red_red(t_token *head)
{
	write(2, "my_bash: syntax error near unexpected token '", 45);
	write(2, head->content, ft_strlen(head->content));
	write(2, "'\n", 2);
	exit_status(258, 1);
}

int	syntax_error(t_token *head)
{
	if (ft_red(head) && head->next && ft_red(head->next))
	{
		red_red(head->next);
		return (-1);
	}
	if (ft_red(head) && head->next == NULL)
	{
		error_red();
		return (-1);
	}
	if ((ft_red(head) && head->next && head->next->type == Pipe) || \
	(head->type == Pipe && head->next && ft_red(head->next) && \
	!head->next->next) || (head->type == Pipe && head->next == NULL) || \
	(head->type == Pipe && head->next->type == Pipe))
	{
		error_pipe();
		return (-1);
	}
	return (1);
}

int	check_for_pipe(t_token	*token)
{
	t_token	*head;

	head = token;
	if (head && head->type == Pipe)
	{
		error_pipe();
		return (-1);
	}
	while (head)
	{
		if (syntax_error(head) == -1)
			return (-1);
		head = head->next;
	}
	return (1);
}
