/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:45:03 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/23 22:23:48 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_file_name(t_cmds *command)
{
	char	*name;

	name = check_for_file(command->data[0]);
	if (command->type == file && command->exp == 1 && (ft_strchr(name, ' ')
			|| (!name[0])))
	{
		command->prev->fd = -1;
		write(2, "ambiguous redirect\n", 20);
		exit_status(1, 1);
		return (NULL);
	}
	return (name);
}

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
		*stop = 1;
		perror("");
		exit_status(1, 1);
		return (-1);
	}
	return (1);
}

int	ft_open_files(t_cmds *command)
{
	t_cmds		*tmp;
	int			print_flag;
	int			stop;

	print_flag = 0;
	tmp = command;
	while (tmp)
	{
		stop = 0;
		while (tmp && tmp->type != Pipe)
		{
			if (tmp->type == REDIRECT_IN)
				ft_red_in(tmp, &stop);
			else if (tmp->type == REDIRECT_OUT && !stop)
				ft_red_out(tmp);
			else if (tmp->type == APPEND && !stop)
				ft_append(tmp);
			tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}
