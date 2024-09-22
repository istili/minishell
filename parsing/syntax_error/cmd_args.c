/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:06:01 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/22 23:30:47 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	file_arg(t_token *token)
{
	while (token)
	{
		if (token->type == file && token->next && token->next->type == ARG)
			return (1);
		token = token->next;
	}
	return (0);
}

void	special_case(t_token **token)
{
	printf("data : %s\n", (*token)->content);
	if (ft_red(*token) && !file_arg(*token))
		check_for_cmd_red_args(token);
	else if (file_arg(*token))
		check_for_cmd_red_args(token);
}

void	ft_change(t_token **h, t_token **t, t_token *first, t_token *second)
{
	second->next = (*h)->next;
	if ((*h)->next)
		(*h)->next->prev = second;
	if (first->prev)
	{
		(*h)->prev = first->prev;
		first->prev->next = (*h);
		(*h)->next = first;
		first->prev = (*h);
	}
	else
	{
		(*h)->next = first;
		first->prev = (*h);
		(*h)->prev = NULL;
		*t = *h;
	}
}

void	check_for_cmd_red_args(t_token **token)
{
	t_token	*head;
	t_token	*first;
	t_token	*second;

	head = *token;
	second = NULL;
	first = NULL;
	while (head)
	{
		while (head && head->type != Pipe)
		{
			if ((head->type == file || head->type == DELIMITER) && head->prev)
			{
				second = head;
				first = head->prev;
			}
			if (head->type == ARG && (head->prev->type == file || \
			head->prev->type == DELIMITER))
				ft_change(&head, token, first, second);
			head = head->next;
		}
		if (head)
			head = head->next;
	}
	special_case(token);
}
