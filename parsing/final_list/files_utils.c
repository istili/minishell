/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:19:20 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/24 20:54:21 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*check_for_file(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str) - 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (len >= 0 && (str[len] == ' ' || str[len] == '\t'))
		len --;
	str[len + 1] = '\0';
	return (str + i);
}

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

void	close_fd(t_cmds *cmd)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	if (cmd->herdoc != 0)
		close(cmd->herdoc);
}
