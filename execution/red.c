/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 22:37:20 by istili            #+#    #+#             */
/*   Updated: 2024/09/24 20:40:24 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_herdoc(t_cmds *cmds)
{
	int	flag;
	int	fd;

	fd = 0;
	flag = 0;
	while (cmds->next && cmds->next->type != Pipe)
		cmds = cmds->next;
	while (cmds && cmds->type != Pipe)
	{
		if (flag && cmds->type == HEREDOC)
			close(cmds->fd_h);
		if (!flag && cmds->type == HEREDOC)
		{
			flag = 1;
			fd = cmds->fd_h;
		}
		cmds = cmds->prev;
	}
	return (fd);
}

int	find_red_in(t_cmds *cmds)
{
	int	flag;
	int	fd;

	fd = 0;
	flag = 0;
	while (cmds->next && cmds->next->type != Pipe)
		cmds = cmds->next;
	while (cmds && cmds->type != Pipe)
	{
		if (flag && cmds->type == REDIRECT_IN)
			close(cmds->fd);
		if (!flag && cmds->type == REDIRECT_IN)
		{
			flag = 1;
			if (cmds->fd != 0)
				fd = cmds->fd;
		}
		cmds = cmds->prev;
	}
	return (fd);
}

int	find_red_out(t_cmds *cmds)
{
	int	flag;
	int	fd;

	fd = 1;
	flag = 0;
	while (cmds->next && cmds->next->type != Pipe)
		cmds = cmds->next;
	while (cmds && cmds->type != Pipe)
	{
		if (flag && (cmds->type == REDIRECT_OUT || cmds->type == APPEND))
			close(cmds->fd);
		if (!flag && (cmds->type == REDIRECT_OUT || cmds->type == APPEND))
		{
			flag = 1;
			if (cmds->fd != 1)
				fd = cmds->fd;
		}
		cmds = cmds->prev;
	}
	return (fd);
}

int	no_red(t_cmds *cmd)
{
	while (cmd->next && cmd->next->type != Pipe)
	{
		if (cmd->type == REDIRECT_IN || cmd->type == HEREDOC
			|| cmd->type == REDIRECT_OUT || cmd->type == APPEND)
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

int	heredoc_is_last(t_cmds *cmds)
{
	while (cmds->next && cmds->next->type != Pipe)
		cmds = cmds->next;
	while (cmds)
	{
		if (cmds->type == HEREDOC)
			return (1);
		else if (cmds->type == REDIRECT_IN || cmds->type == Pipe)
			break ;
		cmds = cmds->prev;
	}
	return (0);
}
