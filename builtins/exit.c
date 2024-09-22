/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:10:11 by istili            #+#    #+#             */
/*   Updated: 2024/09/22 22:12:57 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (!s[i])
		return (1);
	return (0);
}

int	handle_exit_error(char **av, t_link *envp)
{
	if (av[1] && !is_number(av[1]))
	{
		if (!envp->pipe)
			write(2, "exit\n", 5);
		write(2, "my_bash: exit: numeric argument required\n", 41);
		ft_malloc_gab(0, 1);
		exit(255);
	}
	if (av[1] && av[2] && !is_number(av[1]))
	{
		if (!envp->pipe)
			write(2, "exit\n", 5);
		write(2, "my_bash: exit: too many arguments\n", 34);
		exit_status(1, 1);
		return (1);
	}
	return (0);
}

void	f_exit(t_link *envp, char **av)
{
	int	status;

	status = 0;
	if (av[1] == 0)
	{
		if (!envp->pipe)
			write(2, "exit\n", 5);
		ft_malloc_gab(0, 1);
		exit(0);
	}
	if (handle_exit_error(av, envp) == 1)
		return ;
	else if (!envp->pipe)
		write(2, "exit\n", 5);
	status = ft_atoi(av[1]);
	exit_status(status, 1);
	ft_malloc_gab(0, 1);
	exit(status);
}
