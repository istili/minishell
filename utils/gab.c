/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:21:38 by istili            #+#    #+#             */
/*   Updated: 2024/08/23 11:42:26 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_gab(void *ptr, t_list *som)
{
	t_gab	*node;
	t_gab	*tmp;

	node = malloc(sizeof(t_node));
	if (!node)
		error(MALLOC);
	node->next = NULL;
	node->ptr = ptr;
	if (!som->head)
	{
		som->head = node;
		return ;
	}
	tmp = som->head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

static void	free_gab(t_list *som)
{
	t_gab	*node;
	t_gab	*other;

	node = som->head;
	while (node)
	{
		other = node;
		node = node->next;
		free(other->ptr);
		free(other);
	}
}

void	*ft_malloc_gab(size_t size, int flag)
{
	static t_list	som;
	void			*p;

	if (flag == 1)
	{
		(void)size;
		free_gab(&som);
		return (NULL);
	}
	p = malloc(size);
	if (!p)
		error(MALLOC);
	add_gab(p, &som);
	return (p);
}
