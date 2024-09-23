/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:52:37 by istili            #+#    #+#             */
/*   Updated: 2024/09/23 21:29:59 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**find_path(char **env)
{
	int		i;
	char	**splited_path;

	i = 0;
	splited_path = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			splited_path = ft_split(env[i] + 5, ':', ':');
			break ;
		}
		i++;
	}
	return (splited_path);
}

static int	clean_path(char **env, t_cmds *command)
{
	int		i;
	char	**path;

	i = 0;
	path = find_path(env);
	if (!path)
		return (1);
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], *(command->data));
		if (!access(path[i], F_OK) && command->data[0][0] != '\0')
		{
			*(command->data) = path[i];
			return (1);
		}
		i++;
	}
	return (0);
}

int	fill_cmd(t_cmds *cmds, char **env)
{
	struct stat	stat_file;

	if (ft_strchr(cmds->data[0], '/'))
	{
		if (!stat(cmds->data[0], &stat_file) && S_ISDIR(stat_file.st_mode))
		{
			write(2, cmds->data[0], ft_strlen(cmds->data[0]));
			write(2, " :is a Directory\n", 17);
			return (exit_status(126, 1), 1);
		}
	}
	else
		clean_path(env, cmds);
	if (cmds->data[0] && cmds->data[0][1] == '/' &&
		!access(cmds->data[0], F_OK) && access(cmds->data[0], X_OK))
	{
		write(2, cmds->data[0], ft_strlen(cmds->data[0]));
		write(2, " :Permission denied\n", 20);
		return (exit_status(126, 1), 1);
	}
	return (0);
}
