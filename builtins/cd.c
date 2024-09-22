/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:41:45 by istili            #+#    #+#             */
/*   Updated: 2024/09/22 21:22:35 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_home(t_link *envp)
{
	char	*path;
	char	*home;

	home = find_home_path(envp);
	if (!home)
	{
		write(2, "my_bash: cd: HOME not set\n", 27);
		exit_status(1, 1);
		return (1);
	}
	if (home[0] == '\0')
		return (exit_status(0, 1), 0);
	path = ft_strdup(home);
	updatenv(envp, "OLDPWD", ft_strdup(envp->pwd));
	envp->pwd = path;
	updatenv(envp, "PWD", ft_strdup(envp->pwd));
	if (chdir(path) != 0)
	{
		write(2, "my_bash: cd: ", 10);
		write(2, path, ft_strlen(path));
		perror(" ");
		exit_status(1, 1);
		return (1);
	}
	return (exit_status(0, 1), 0);
}

static int	cd_something(t_link *envp, char *target)
{
	char	*full_path;

	write(2, "cd: error retrieving current directory:", 39);
	write(2, "getcwd: cannot access parent directories:", 41);
	write(2, "No such file or directory\n", 26);
	updatenv(envp, "OLDPWD", ft_strdup(envp->pwd));
	full_path = ft_strjoin(ft_strdup(envp->pwd), "/");
	full_path = ft_strjoin(full_path, target);
	envp->pwd = full_path;
	updatenv(envp, "PWD", ft_strdup(envp->pwd));
	return (exit_status(0, 1), 0);
}

int	f_cd(char **target_path, t_link *envp)
{
	char	*target;
	char	*pwd;

	target = target_path[1];
	if (target == NULL)
		return (cd_home(envp));
	else if (target && target[0] == '\0')
		return (exit_status(0, 1), 0);
	if (chdir(target) != 0)
	{
		write(2, "my_bash: cd: ", 14);
		write(2, target, ft_strlen(target));
		perror(" ");
		return (exit_status(1, 1), 1);
	}
	pwd = ft_strdup_del(getcwd(NULL, 0));
	if (!pwd)
		return (cd_something(envp, target));
	updatenv(envp, "OLDPWD", ft_strdup(envp->pwd));
	envp->pwd = pwd;
	updatenv(envp, "PWD", ft_strdup(envp->pwd));
	return (exit_status(0, 1), 0);
}
