/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:41:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/13 00:13:38 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_len_args(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	ft_len(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}

t_token	*ft_lst_new(int len)
{
	t_token	*command;

	command = ft_malloc_gab(sizeof(t_token), 0);
	command->data = ft_malloc_gab(sizeof(char *) * (len + 1), 0);
	command->next = NULL;
	command->prev = NULL;
	return (command);
}

int	ft_store_data(t_token **command, t_token *token, int j, int len)
{
	t_token	*tmp;
	t_token	*last;

	tmp = NULL;
	if (!token->prev || ft_red(token) || token->type == Pipe || \
	ft_red(token->prev) || token->prev->type == Pipe)
	{
		j = 0;
		tmp = ft_lst_new(len);
		to_next_node(command, tmp);
		final_enum(token, command);
	}
	last = ft_lstlast(*command);
	last->data[j] = ft_strdup(token->content);
	if (token->exp >= 1)
		last->exp = 1;
	else
		last->exp = 0;
	if (token->quotes == 2 || token->quotes == 1)
		last->quotes = token->quotes;
	return (j);
}

t_token	*ft_new_list(t_token *token)
{
	t_token	*command;
	t_token	*head;
	t_token	*lst;
	int		j;
	int		len;

	command = NULL;
	head = token;
	len = ft_len(head);
	j = 0;
	while (head)
	{
		j = ft_store_data(&command, head, j, len);
		if (head->next == NULL || head->next->type == Pipe || \
		ft_red(head->next) || head->type == Pipe || \
		ft_red(head))
		{
			lst = ft_lstlast(command);
			lst->data[j + 1] = NULL;
		}
		j++;
		head = head->next;
	}
	return (command);
}
