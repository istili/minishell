/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_my_own_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:20:28 by istili            #+#    #+#             */
/*   Updated: 2024/09/15 19:10:18 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_node(t_link *node, void *env)
{
	t_node	*last_node;
	t_node	*new_node;

	new_node = ft_malloc_gab(sizeof(t_node), 0);
	if (!node->head)
	{
		node->head = new_node;
		new_node->prv = NULL;
	}
	else
	{
		last_node = node->tail;
		last_node->next = new_node;
		new_node->prv = last_node;
	}
	new_node->next = NULL;
	new_node->data = env;
	node->tail = new_node;
	node->size++;
}

static t_env	*make_pair_env(char *key, char *val)
{
	t_env	*env;

	env = ft_malloc_gab(sizeof(t_env), 0);
	env->key = ft_strdup(key);
	if (val)
		env->val = ft_strdup(val);
	else
		env->val = NULL;
	return (env);
}

t_link	*make_my_own_env(void)
{
	t_link	*linkedlist;

	linkedlist = ft_malloc_gab(sizeof(t_link), 0);
	linkedlist->head = NULL;
	linkedlist->tail = NULL;
	linkedlist->size = 0;
	linkedlist->pwd = ft_strdup_del(getcwd(NULL, 0));
	linkedlist->env_indx = 1;
	add_node(linkedlist, make_pair_env("PWD", linkedlist->pwd));
	add_node(linkedlist, make_pair_env("SHLVL", "1"));
	add_node(linkedlist, make_pair_env("_", "/usr/bin/env"));
	add_node(linkedlist, make_pair_env("OLDPWD", NULL));
	add_node(linkedlist, make_pair_env("PATH", "/Users/istili/.brew/bin:/usr/local/bin: \
		/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin: \
		/Users/istili/.brew/bin"));
	return (linkedlist);
}
