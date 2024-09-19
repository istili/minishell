/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:48:19 by istili            #+#    #+#             */
/*   Updated: 2024/09/17 02:18:18 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	infinite_lop(t_link *envp, t_exc fd)
{
	t_cmds			*cmds;
	struct termios	term;

	tcgetattr(envp->zero, &term);
	envp->term = &term;
	while (1)
	{
		cmds = read_line(envp);
		if (!cmds)
			continue ;
		signal(SIGINT, SIG_IGN);
		execution(envp, cmds);
		signal(SIGINT, handle_siginit);
		dup2(fd.zero, 0);
		dup2(fd.one, 1);
	}
}

void	init_env(char **env, t_link **envp)
{
	if (*env == NULL)
		*envp = make_my_own_env();
	else
		*envp = env_linkedlist(env);
}

t_token	*n_node(t_token *current, t_token *token)
{
	current = ft_malloc_gab(sizeof(t_token), 0);
	current->content = ft_strdup(token->content);
	current->flag = token->flag;
	current->exp = token->exp;
	if (token->quotes == 2 || token->quotes == 1)
		current->quotes = token->quotes;
	current->next = NULL;
	current->prev = NULL;
	return (current);
}

void	store_it(t_token *current, t_token *token, t_token **head_ref)
{
	t_token	*last;

	last = NULL;
	current = n_node(current, token);
	if (*head_ref == NULL)
		*head_ref = current;
	else
	{
		last = *head_ref;
		while (last->next != NULL)
			last = last->next;
		last->next = current;
		current->prev = last;
	}
}

int	convert_it(char *line, t_token **head_ref, t_link *envp)
{
	t_token	*token;
	t_token	*current;

	token = ft_tokenizer(line, envp);
	current = NULL;
	if (token == NULL)
		return (-1);
	while (token)
	{
		if (token->content[0] == '\0' && token->exp >= 1 && \
		!token->next && !token->prev)
			return (-1);
		else if (token->content[0] == '\0' && token->exp >= 1 && \
		ft_si(token->prev) == 0)
			token = token->next;
		else
		{
			store_it(current, token, head_ref);
			token = token->next;
		}
	}
	return (1);
}
