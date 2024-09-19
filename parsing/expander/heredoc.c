/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:20:25 by istili            #+#    #+#             */
/*   Updated: 2024/09/18 23:16:15 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)b;
	i = 0;
	while (len > i)
	{
		str[i] = c;
		i++;
	}
	return (b);
}

char	*herdoc_read(char *h_d, t_cmds *commands, t_link *envp)
{
	char	*tmp;

	h_d = ft_strdup_del(readline("> "));
	if (!h_d)
		return (NULL);
	if (ft_strcmp(h_d, commands->next->data[0]) == 0)
		return (NULL);
	if (commands->next->quotes == 2 || commands->next->quotes == 1)
		return (h_d);
	if (ft_strchr(h_d, '$') != NULL )
	{
		tmp = heredoc_expander(h_d, envp);
		h_d = ft_memset(h_d, 0, ft_strlen(h_d));
		h_d = ft_strdup(tmp);
	}
	return (h_d);
}

char	*open_herdoc_file(t_cmds *commands, char *file, int *fd)
{
	char	*path;

	path = ft_strdup("/tmp/");
	if (!path)
		return (NULL);
	file = ft_strjoin(path, "heredoc");
	*fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	commands->fd_h = open(file, O_RDWR);
	if (*fd == -1)
	{
		perror("my_bash: ");
		return (NULL);
	}
	unlink(file);
	return (file);
}

int	fill_file(int fd, t_cmds *commands, t_link *envp, char *file)
{
	char	*h_d;

	h_d = NULL;
	signal(SIGINT, handle_herdoc);
	h_d = herdoc_read(h_d, commands, envp);
	signal(SIGINT, handle_siginit);
	if (!h_d)
	{
		unlink(file);
		return (-1);
	}
	ft_putstr_fd(h_d, fd);
	return (1);
}

int	heredoc(t_cmds *commands, t_link *envp)
{
	char	*file;
	int		fd;

	file = NULL;
	fd = 0;
	while (commands)
	{
		if (ft_strcmp(commands->data[0], "<<") == 0)
		{
			file = open_herdoc_file(commands, file, &fd);
			if (!file)
				return (-1);
			while (true)
			{
				if (fill_file(fd, commands, envp, file) == -1)
					break ;
			}
			close(fd);
			unlink(file);
		}
		commands = commands->next;
	}
	return (1);
}
