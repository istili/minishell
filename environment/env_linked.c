/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:15:51 by istili            #+#    #+#             */
/*   Updated: 2024/08/12 00:38:26 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_fake_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == '\0')
		return (i);
	return (-1);
}

static t_link	*allocet_linkedlist(t_link *linkedlist)
{
	linkedlist = ft_malloc_gab(sizeof(t_link), 0);
	linkedlist->head = NULL;
	linkedlist->tail = NULL;
	linkedlist->size = 0;
	linkedlist->pwd = ft_strdup_del(getcwd(NULL, 0));
	linkedlist->env_indx = 0;
	return (linkedlist);
}

static t_env	**allocate_env(char **env, t_env **envp)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	envp = ft_malloc_gab(sizeof(t_env *) * i, 0);
	return (envp);
}

static char	*check_shlvl(char *key, char *val)
{
	int	shlvl;

	if (!ft_strcmp(key, "SHLVL"))
	{
		if (is_number(val))
		{
			shlvl = ft_atoi(val);
			if (shlvl == 999)
				val = NULL;
			else if (shlvl > 999)
				val = ft_itoa(1);
			else if (shlvl < 0)
				val = ft_itoa(0);
			else
				val = ft_itoa(shlvl + 1);
		}
		else
			val = ft_itoa(1);
	}
	return (val);
}

t_link	*env_linkedlist(char **env)
{
	int		i;
	int		j;
	t_link	*linkedlist;
	t_env	**envp;

	j = 0;
	envp = NULL;
	linkedlist = NULL;
	envp = allocate_env(env, envp);
	linkedlist = allocet_linkedlist(linkedlist);
	i = -1;
	while (env[++i])
	{
		j = ft_fake_strchr(env[i], '=');
		if (j == -1)
			j = ft_strlen(env[i]);
		envp[i] = ft_malloc_gab(sizeof(t_env), 0);
		envp[i]->key = ft_substr(env[i], 0, j);
		envp[i]->val = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j + 1);
		envp[i]->val = check_shlvl(envp[i]->key, envp[i]->val);
		add_node(linkedlist, envp[i]);
	}
	return (linkedlist);
}
