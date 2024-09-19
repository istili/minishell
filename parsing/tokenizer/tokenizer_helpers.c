/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:59:54 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/17 02:31:02 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup(const char *s)
{
	size_t		len ;
	char		*str;
	int			i;

	i = 0;
	len = ft_strlen(s);
	str = ft_malloc_gab(len + 1, 0);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

t_token	*lst_new(t_link *envp, int len)
{
	t_token	*node;

	node = ft_malloc_gab(sizeof(t_token), 0);
	node->content = ft_malloc_gab(len + 1, 0);
	node->next = NULL;
	node->prev = NULL;
	envp->j = 0;
	return (node);
}

t_token	*ft_lstlast(t_token *data)
{
	if (!data)
		return (NULL);
	while (data->next)
		data = data->next;
	return (data);
}

void	to_next_node(t_token **token, t_token *data)
{
	t_token	*nod;

	if (!(*token))
	{
		(*token) = data;
		return ;
	}
	nod = ft_lstlast((*token));
	nod->next = data;
	data->prev = nod;
	data->next = NULL;
}

int	ft_writ(char c)
{
	if (c == '\0')
	{
		write(2, "unclosed double qoutes\n", 24);
		exit_status(258, 1);
		return (-1);
	}
	return (1);
}
