/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:45:03 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/24 20:53:31 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_red_out(t_cmds *command)
{
	char	*name;

	if (command->next && !(ft_file_name(command->next)))
		return (-1);
	else
		name = ft_file_name(command->next);
	command->fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (command->fd == -1 && !herdoc_c_signal(0, 0))
	{
		command->fd = -1;
		perror("");
		exit_status(1, 1);
		return (-1);
	}
	return (1);
}

int	ft_append(t_cmds *command)
{
	char	*name;

	if (command->next && !(ft_file_name(command->next)))
		return (-1);
	else
		name = ft_file_name(command->next);
	command->fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (command->fd == -1 && !herdoc_c_signal(0, 0))
	{
		command->fd = -1;
		perror("");
		exit_status(1, 1);
		return (-1);
	}
	return (1);
}

int	ft_red_in(t_cmds *command, int *stop)
{
	char		*name;

	if (command->next && !(ft_file_name(command->next)))
		return (-1);
	else
		name = ft_file_name(command->next);
	command->fd = open(name, O_RDONLY, 0644);
	if (command->fd == -1 && !herdoc_c_signal(0, 0))
	{
		command->fd = -1;
		*stop = 1;
		perror("");
		exit_status(1, 1);
		return (-1);
	}
	return (1);
}

void	open_helper(int *stop, t_cmds **tmp)
{
	t_cmds		*tmp2;

	while ((*tmp) && (*tmp)->type != Pipe)
	{
		if ((*tmp)->type == REDIRECT_IN)
			ft_red_in((*tmp), stop);
		else if ((*tmp)->type == REDIRECT_OUT && !*stop)
			ft_red_out((*tmp));
		else if ((*tmp)->type == APPEND && !*stop)
			ft_append((*tmp));
		if (*stop)
		{
			tmp2 = (*tmp);
			while ((*tmp) && (*tmp)->type != Pipe)
			{
				if ((*tmp)->type == REDIRECT_OUT
					|| (*tmp)->type == APPEND || (*tmp)->type == REDIRECT_IN)
					(*tmp)->fd = -1;
				(*tmp) = (*tmp)->next;
			}
			(*tmp) = tmp2;
			break ;
		}
		(*tmp) = (*tmp)->next;
	}
}

int	ft_open_files(t_cmds *command)
{
	t_cmds		*tmp;
	int			stop;

	tmp = command;
	stop = 0;
	while (tmp)
	{
		if (stop)
		{
			while (tmp && tmp->type != Pipe)
				tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
		}
		stop = 0;
		open_helper(&stop, &tmp);
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}
