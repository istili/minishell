/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:41:30 by istili            #+#    #+#             */
/*   Updated: 2024/09/23 22:30:42 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	replace(t_link *linkedlist, char *key, char *val, int flag)
{
	t_node	*node;
	t_env	*env;

	node = linkedlist->head;
	while (node)
	{
		env = node->data;
		if (!ft_strcmp(env->key, key) && val == NULL)
			return ;
		if (!ft_strcmp(env->key, key))
		{
			if (flag == 1)
			{
				env->val = ft_strjoin(env->val, val);
				return ;
			}
			env->val = val;
			return ;
		}
		node = node->next;
	}
	env = ft_malloc_gab(sizeof(t_env), 0);
	env->key = key;
	env->val = val;
	add_node(linkedlist, env);
}

static void	export_printer(t_link *linkedlist)
{
	t_node	*head;
	t_env	*env;

	head = linkedlist->head;
	while (head)
	{
		env = head->data;
		if (!ft_strcmp(env->key, "_") && linkedlist->env_indx)
			head = head->next;
		else
		{
			if (linkedlist->env_indx && !ft_strcmp(env->key, "PATH"))
			{
				head = head->next;
				continue ;
			}
			printf("declare -x %s", (char *)env->key);
			if (env->val)
				printf("=\"%s\"", (char *)env->val);
			printf("\n");
			head = head->next;
		}
	}
}

static void	looop(t_link *linkedlist, char **av, int *status)
{
	int		i;
	char	*key;
	char	*val;
	int		flag;

	i = -1;
	key = NULL;
	val = NULL;
	*status = 0;
	while (av[++i])
	{
		flag = 0;
		if (check_arg(av[i]) == 1)
		{
			write(2, "my_bash: export: `", 19);
			write(2, av[i], ft_strlen(av[i]));
			write(2, ": not a valid identifier\n", 25);
			i++;
			*status = 1;
			continue ;
		}
		key = find_key(av[i], &flag);
		val = find_value(av[i]);
		replace(linkedlist, key, val, flag);
	}
}

void	f_export(t_link *linkedlist, char **av, int exp)
{
	int		status;

	status = 0;
	if (av[1] == NULL || (exp >= 1 && !ft_strchr(av[1], '=')
			&& av[2] == NULL && !av[1][0]))
	{
		export_printer(linkedlist);
		exit_status(status, 1);
		return ;
	}
	looop(linkedlist, av, &status);
	exit_status(status, 1);
}
