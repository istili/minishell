/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 23:44:58 by istili            #+#    #+#             */
/*   Updated: 2024/09/22 22:58:25 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtins(t_cmds *commands, t_link *envp)
{
	if (!ft_strcmp(commands->data[0], "export"))
		f_export(envp, commands->data, commands->exp);
	else if (!ft_strcmp(commands->data[0], "env")
		|| !ft_strcmp(commands->data[0], "ENV"))
		f_env(envp);
	else if (!ft_strcmp(commands->data[0], "exit"))
		f_exit(envp, commands->data);
	else if (!ft_strcmp(commands->data[0], "echo")
		|| !ft_strcmp(commands->data[0], "ECHO"))
		f_echo(commands->data);
	else if (!ft_strcmp(commands->data[0], "pwd")
		|| !ft_strcmp(commands->data[0], "PWD"))
		f_pwd(envp);
	else if (!ft_strcmp(commands->data[0], "unset"))
		f_unset(envp, commands->data);
	else if (!ft_strcmp(commands->data[0], "cd")
		|| !ft_strcmp(commands->data[0], "CD"))
	{
		if (!ft_strcmp(commands->data[0], "cd"))
			f_cd(commands->data, envp);
	}
}

int	is_not_builtin(t_cmds *cmd)
{
	if (!ft_strcmp(cmd->data[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->data[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->data[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmd->data[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd->data[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->data[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->data[0], "cd"))
		return (1);
	else
		return (0);
}

int	rideracting(t_cmds *cmd)
{
	cmd->fd_out = find_red_out(cmd);
	cmd->fd_in = find_red_in(cmd);
	cmd->herdoc = find_herdoc(cmd);
	if ((cmd->type == HEREDOC || cmd->type == APPEND
			|| cmd->type == REDIRECT_IN || cmd->type == REDIRECT_OUT)
		|| (cmd->fd_in == -1 || cmd->fd_out == -1 || cmd->herdoc == -1)
		|| (herdoc_c_signal(0, 0)))
	{
		if (herdoc_c_signal(0, 0))
			exit_status(1, 1);
		close_fd(cmd);
		return (0);
	}
	return (1);
}

char	**link_to_arr(t_link *link)
{
	t_node	*node;
	t_env	*env;
	char	**ret;
	int		i;

	i = 0;
	ret = ft_malloc_gab((link->size + 1) * sizeof(char *), 0);
	node = link->head;
	while (node)
	{
		env = node->data;
		ret[i] = ft_strdup(env->key);
		ret[i] = ft_strjoin(ret[i], "=");
		ret[i] = ft_strjoin(ret[i], env->val);
		i++;
		node = node->next;
	}
	ret[i] = NULL;
	return (ret);
}
