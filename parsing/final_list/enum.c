/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:16:28 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/15 11:49:55 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token_type	token_content_type(t_token *token)
{
	t_token_type	type;

	type = -1;
	if (is_separator(token->content[0]) && token->flag != 1)
	{
		if (ft_strcmp(token->content, "|") == 0)
			type = Pipe;
		else if (ft_strcmp(token->content, "<") == 0)
			type = REDIRECT_IN;
		else if (ft_strcmp(token->content, ">") == 0)
			type = REDIRECT_OUT;
		else if (ft_strcmp(token->content, ">>") == 0)
			type = APPEND;
		else if (ft_strcmp(token->content, "<<") == 0)
			type = HEREDOC;
		else
			type = ft_error();
	}
	return (type);
}

int	checker(t_token	**head)
{
	if (token_content_type((*head)) == Pipe)
	{
		(*head)->type = Pipe;
		(*head) = (*head)->next;
		return (-1);
	}
	else if (token_content_type((*head)) == REDIRECT_IN)
	{
		(*head)->type = REDIRECT_IN;
		(*head) = (*head)->next;
		return (-1);
	}
	else if (token_content_type((*head)) == REDIRECT_OUT)
	{
		(*head)->type = REDIRECT_OUT;
		(*head) = (*head)->next;
		return (-1);
	}
	return (1);
}

int	enumeration(t_token *var)
{
	t_token	*head;

	head = var;
	while (head)
	{
		if (token_content_type(head) == none)
			return (-1);
		if (checker(&head) == -1)
			continue ;
		else if (token_content_type(head) == APPEND)
			head->type = APPEND;
		else if (token_content_type(head) == HEREDOC)
			head->type = HEREDOC;
		else if (!head->prev || token_content_type(head->prev) == Pipe)
			head->type = COMMAND;
		else if (ft_si(head->prev))
			head->type = file;
		else if (token_content_type(head->prev) == HEREDOC)
			head->type = DELIMITER;
		else
			head->type = ARG;
		head = head->next;
	}
	return (1);
}

void	final_enum(t_token *token, t_token **commands)
{
	t_token	*last;

	last = ft_lstlast(*commands);
	if (token->type == Pipe)
		last->type = Pipe;
	else if (token->type == REDIRECT_IN)
		last->type = REDIRECT_IN;
	else if (token->type == REDIRECT_OUT)
		last->type = REDIRECT_OUT;
	else if (token->type == APPEND)
		last->type = APPEND;
	else if (token->type == HEREDOC)
		last->type = HEREDOC;
	else if (token->type == COMMAND)
		last->type = COMMAND;
	else if (token->type == file)
		last->type = file;
	else if (token->type == DELIMITER)
		last->type = DELIMITER;
}
