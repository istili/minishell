/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:48:28 by istili            #+#    #+#             */
/*   Updated: 2024/09/24 17:19:01 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	reset_terminal(t_link *envp)
{
	if (tcsetattr(envp->zero, TCSAFLUSH, envp->term) == -1)
		return ;
}

void	setexit(int status, t_link *envp)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			reset_terminal(envp);
			printf("Quit: 3\n");
		}
		else if (WTERMSIG(status) == 2)
			printf("\n");
		exit_status(WTERMSIG(status) + 128, 1);
	}
	else
		exit_status(WEXITSTATUS(status), 1);
}
