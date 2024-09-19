/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:26:17 by istili            #+#    #+#             */
/*   Updated: 2024/09/16 22:17:04 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_check(char *av)
{
	int	i;

	if (ft_strlen(av) < 2)
		return (0);
	i = 1;
	while (av && av[i] && av[0] == '-' && av[i] == 'n')
		i++;
	if (!av[i])
		return (1);
	return (0);
}

void	f_echo(char **av)
{
	int	i;
	int	new_line;
	int	flag;

	i = 1;
	flag = 0;
	new_line = 0;
	while (av[i])
	{
		if (!flag && echo_check(av[i]) == 1)
		{
			new_line = 1;
			i++;
			continue ;
		}
		flag = 1;
		write(1, av[i], ft_strlen(av[i]));
		i++;
		if (av[i])
			write(1, " ", 1);
	}
	if (!new_line)
		write(1, "\n", 1);
	exit_status(0, 1);
}
