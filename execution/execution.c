/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:55:59 by istili            #+#    #+#             */
/*   Updated: 2024/09/23 00:53:54 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	one_cmd_child(t_cmds *cmd, t_link *envp, char **env, int *status)
{
	if (!rideracting(cmd))
		exit(*status);
	if (cmd->herdoc != 0 && heredoc_is_last(cmd))
		cmd->fd_in = cmd->herdoc;
	if (dup2(cmd->fd_in, 0) == -1)
		error(DUP2, cmd);
	if (dup2(cmd->fd_out, 1) == -1)
		error(DUP2, cmd);
	if (envp->builtin_indx == 1)
	{
		builtins(cmd, envp);
		*status = exit_status(0, 0);
		exit(*status);
	}
	if (execve(cmd->data[0], cmd->data, env) == -1)
	{
		if ((ft_strchr(cmd->data[0], '/') && \
		access(cmd->data[0], F_OK)) || cmd->data[0] == NULL)
			write(2, "no such file or directory\n", 26);
		else
			write(2, "command not found\n", 19);
		*status = 127;
		exit(*status);
	}
}

void	close_fd(t_cmds *cmd)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	if (cmd->herdoc != 0)
		close(cmd->herdoc);
}

static void	pipex(t_link *envp, t_cmds *cmd)
{
	char	**env;

	env = link_to_arr(envp);
	envp->builtin_indx = is_not_builtin(cmd);
	if (envp->builtin_indx == 0)
	{
		if (fill_cmd(cmd, env) == 1)
		{
			close_fd(cmd);
			return ;
		}
	}
	if (envp->pipe_indx == 1)
	{
		if (pipe(envp->fd) == -1)
			error(PIPE, cmd);
	}
	cmd->fd_out = find_red_out(cmd);
	cmd->fd_in = find_red_in(cmd);
	cmd->herdoc = find_herdoc(cmd);
	executing(cmd, env, envp);
}

static int	only_builtin(t_cmds *cmds, t_link *envp)
{
	if (is_it_one_cmd(cmds) && is_not_builtin(cmds) && no_red(cmds))
	{
		builtins(cmds, envp);
		return (0);
	}
	return (1);
}

int	execution(t_link *envp, t_cmds *cmds)
{
	t_cmds	*tmp;
	t_cmds	*cur;

	tmp = cmds;
	envp->pipe = count_pipes(cmds);
	if (!only_builtin(cmds, envp))
		return (0);
	while (tmp)
	{
		envp->pipe_indx = 0;
		cur = tmp;
		while (tmp)
		{
			if (tmp->type == Pipe)
			{
				envp->pipe_indx = 1;
				break ;
			}
			tmp = tmp->next;
		}
		pipex(envp, cur);
		if (tmp)
			tmp = tmp->next;
	}
	return (herdoc_c_signal(0, 1), 0);
}
