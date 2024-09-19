/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:58:11 by istili            #+#    #+#             */
/*   Updated: 2024/09/04 02:05:44 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_sign(const char *str, int i)
{
	int	sign;

	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	long	nb;
	long	tmp;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\n' || str[i] == ' ')
		i++;
	sign = check_sign(str, i);
	if (str[i] == '-' || str[i] == '+')
		i++;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = nb * 10 + str[i] - '0';
		if (nb > tmp && sign == 1)
			return (-1);
		if (nb > tmp && sign == -1)
			return (0);
		nb = tmp;
		i++;
	}
	return (nb * sign);
}

int	exit_status(int new_status, int flag)
{
	static int	status;

	if (flag)
		status = new_status;
	return (status);
}

int	count_pipes(t_cmds *cmds)
{
	int	count;

	count = 0;
	while (cmds->next)
	{
		if (cmds->type == Pipe)
			count++;
		cmds = cmds->next;
	}
	return (count);
}

int	is_it_one_cmd(t_cmds *cmds)
{
	while (cmds->next)
	{
		if (cmds->type == Pipe)
			return (0);
		cmds = cmds->next;
	}
	return (1);
}
