/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:11:28 by istili            #+#    #+#             */
/*   Updated: 2024/09/24 20:25:45 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_dup(t_cmds *cmd, t_link *envp)
{
	if (cmd->herdoc != 0 && heredoc_is_last(cmd))
		cmd->fd_in = cmd->herdoc;
	if (cmd->fd_in != 0 && dup2(cmd->fd_in, 0) == -1)
		error(DUP2, cmd);
	close(envp->fd[0]);
	if (envp->fd[0] != 1 && dup2(envp->fd[1], 1) == -1)
		error(DUP2, cmd);
	close(envp->fd[1]);
	if (cmd->fd_out != 1 && dup2(cmd->fd_out, 1) == -1)
		error(DUP2, cmd);
}

static void	execute_one_cmd(t_cmds *cmd, char **env, pid_t id, t_link *envp)
{
	int		status;

	status = exit_status(0, 0);
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		one_cmd_child(cmd, envp, env, &status);
	}
	else if (id != 0)
	{
		if (envp->pipe != 0)
			close(0);
		while (waitpid(-1, &status, 0) != -1)
			;
		setexit(status, envp);
	}
}

static void	child(char **env, t_cmds *cmd, t_link *envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!rideracting(cmd))
		exit(0);
	ft_dup(cmd, envp);
	if (envp->builtin_indx == 1)
	{
		builtins(cmd, envp);
		exit(exit_status(0, 0));
	}
	if (execve(cmd->data[0], cmd->data, env) == -1)
	{
		if ((ft_strchr(cmd->data[0], '/') && \
		access(cmd->data[0], F_OK) != 0) || cmd->data[0] == NULL)
			write(2, "no such file or directory\n", 26);
		else
			write(2, "command not found\n", 18);
		exit(1);
	}
}

static void	parent(t_link *envp, t_cmds *cmd)
{
	close(envp->fd[1]);
	if (envp->fd[0] != 0 && dup2(envp->fd[0], 0) == -1)
		error(DUP2, cmd);
	close(envp->fd[0]);
}

void	executing(t_cmds *cmd, char **env, t_link *envp)
{
	pid_t	id;

	id = fork();
	if (id == -1)
		error(FORK, cmd);
	if (envp->pipe_indx == 1)
	{
		if (id != 0)
			parent(envp, cmd);
		else if (id == 0)
			child(env, cmd, envp);
	}
	else
		execute_one_cmd(cmd, env, id, envp);
	close_fd(cmd);
}
