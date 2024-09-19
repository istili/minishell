/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 01:15:02 by istili            #+#    #+#             */
/*   Updated: 2024/09/14 02:06:13 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_siginit(int sig)
{
	if (sig == SIGINT)
	{
		exit_status(1, 1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	herdoc_c_signal(int state, int flag)
{
	static int	s;

	if (flag == 1)
		s = state;
	return (s);
}

void	handle_herdoc(int signumber)
{
	if (signumber == SIGINT)
	{
		herdoc_c_signal(1, 1);
		exit_status(-1, 1);
		rl_replace_line("", 0);
		close(0);
		ioctl(0, TIOCGWINSZ, NULL);
	}
}
