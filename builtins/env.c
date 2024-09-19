/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:47:50 by istili            #+#    #+#             */
/*   Updated: 2024/08/16 23:43:51 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	f_env(t_link *linkedlist)
{
	t_node	*head;
	t_env	*envp;

	head = linkedlist->head;
	while (head)
	{
		envp = head->data;
		if (envp->val != NULL)
		{
			printf("%s", (char *)envp->key);
			if (envp->val)
				printf("=%s", (char *)envp->val);
			printf("\n");
		}
		head = head->next;
	}
	exit_status(0, 1);
}
