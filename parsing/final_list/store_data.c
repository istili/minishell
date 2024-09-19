/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 03:36:57 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/13 00:13:45 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmds	*last_node(t_cmds *data)
{
	if (!data)
		return (NULL);
	while (data->next)
		data = data->next;
	return (data);
}

void	add_nod(t_cmds **token, t_cmds *data)
{
	t_cmds	*nod;

	if (!(*token))
	{
		(*token) = data;
		return ;
	}
	nod = last_node((*token));
	nod->next = data;
	data->prev = nod;
	data->next = NULL;
}

t_cmds	*new_node(int i, t_token *head)
{
	t_cmds	*node;

	node = ft_malloc_gab(sizeof(t_cmds), 0);
	node->data = ft_malloc_gab(sizeof(char *) * (i + 1), 0);
	node->next = NULL;
	node->prev = NULL;
	node->type = head->type;
	return (node);
}

void	store_data(t_cmds	**cmd, t_token	*token)
{
	int		j;
	t_cmds	*last;

	j = 0;
	last = last_node(*cmd);
	while (token->data[j])
	{
		last->data[j] = ft_strdup(token->data[j]);
		j++;
	}
	last->exp = token->exp;
	if (token->quotes == 2 || token->quotes == 1)
		last->quotes = token->quotes;
	last->data[j] = NULL;
}

void	convert_to_new_list(t_token *token, t_cmds **cmnd)
{
	t_token	*command;
	t_token	*head;
	t_cmds	*tmp;
	int		len;

	command = ft_new_list(token);
	head = command;
	while (head)
	{
		len = ft_len_args(head->data);
		tmp = new_node(len, head);
		add_nod(cmnd, tmp);
		store_data(cmnd, head);
		head = head->next;
	}
}
