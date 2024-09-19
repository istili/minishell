/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:23:47 by istili            #+#    #+#             */
/*   Updated: 2024/09/16 22:19:11 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_args(char *av)
{
	int		i;

	i = 0;
	if (is_alpha_(av[0]) == -1)
		return (0);
	while (av[i])
	{
		if (is_alphnum(av[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}

static void	remove_node(t_link *linked, t_node *node_del)
{
	if (linked->head == NULL || node_del == NULL)
		return ;
	if (linked->head == node_del)
		linked->head = node_del->next;
	if (linked->tail == node_del)
		linked->tail = node_del->prv;
	if (node_del->next != NULL)
		node_del->next->prv = node_del->prv;
	if (node_del->prv != NULL)
		node_del->prv->next = node_del->next;
}

int	check_error(char **av, int i)
{
	int	failed;

	failed = 0;
	if (!check_args(av[i]))
	{
		write(2, "unset: `", 8);
		write(2, av[i], ft_strlen(av[i]));
		write(2, "': not a valid identifier\n", 26);
		failed = 1;
	}
	return (failed);
}

void	unset_node(t_node *head, char **av, int i, t_link *linkd)
{
	t_env	*env;

	while (head)
	{
		env = head->data;
		if (!ft_strcmp(av[i], env->key))
		{
			remove_node(linkd, head);
			break ;
		}
		else
			head = head->next;
	}
}

int	f_unset(t_link *linkd, char **av)
{
	int		i;
	t_node	*head;
	int		failed;

	i = 1;
	failed = 0;
	if (!av || !av[i])
		return (failed);
	while (av[i])
	{
		head = linkd->head;
		if (check_error(av, i) == 1)
			failed = 1;
		else
			unset_node(head, av, i, linkd);
		i++;
	}
	return (exit_status(failed, 1), 0);
}
