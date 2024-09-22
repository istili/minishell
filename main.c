/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 02:22:19 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/22 21:01:44 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	f(void)
// {
// 	system("leaks minishell");
// }

char	*read_line_call(void)
{
	char	*line;

	line = ft_strdup_del(readline("my_bash-4.5$ "));
	if (!line)
	{
		write(1, "exit\n", 5);
		exit(exit_status(0, 0));
	}
	if (line[0] == '\0')
		return (NULL);
	if (!full_space(line))
		add_history(line);
	if (!line)
		return (NULL);
	return (line);
}

t_cmds	*read_line(t_link *envp)
{
	t_token	*tok;
	t_cmds	*commands;
	char	*line;

	tok = NULL;
	commands = NULL;
	line = read_line_call();
	if (!line)
		return (NULL);
	if (convert_it(line, &tok, envp) == -1)
		return (NULL);
	if (enumeration(tok) == -1)
		return (NULL);
	if (check_for_pipe(tok) == -1)
		return (NULL);
	check_for_cmd_red_args(&tok);
	convert_to_new_list(tok, &commands);
	if (heredoc(commands, envp) == -1)
		return (NULL);
	if (ft_open_files(commands) == -1)
		return (commands);
	return (commands);
}

int	main(int ac, char **av, char **env)
{
	t_link	*envp;
	t_exc	fd;

	(void)ac;
	(void)av;
	fd.zero = dup(0);
	fd.one = dup(1);
	envp = NULL;
	rl_catch_signals = 0;
	if (!isatty(ttyslot()))
		return (printf("tty required\n"), 0);
	init_env(env, &envp);
	envp->zero = fd.zero;
	envp->one = fd.one;
	signal(SIGINT, handle_siginit);
	signal(SIGQUIT, SIG_IGN);
	infinite_lop(envp, fd);
	close(fd.one);
	close(fd.zero);
	return (0);
}
