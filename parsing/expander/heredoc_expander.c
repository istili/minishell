/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istili <istili@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:12:41 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/13 00:13:15 by istili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	code_status(t_herdoc *var, char *line, t_link *envp)
{
	int	y;

	var->i++;
	var->j = var->i;
	while (line[var->i] && is_alphnum(line[var->i]) == 0)
		var->i++;
	if (line[var->j - 1] == '$' && line[var->i] == '?')
		var->i++;
	var->env = ft_replace(line, var->j, var->i, envp);
	var->size = var->len + var->x + ft_strlen(var->env) + 1;
	var->data = (char *)ft_realloc(var->data, var->size, var->x);
	y = 0;
	while (var->env[y])
	{
		var->data[var->x] = var->env[y];
		var->x++;
		y++;
	}
}

char	*heredoc_expander(char *line, t_link *envp)
{
	t_herdoc	*var;

	var = ft_malloc_gab(sizeof(t_herdoc), 0);
	var->i = 0;
	var->x = 0;
	var->data = ft_malloc_gab(ft_strlen(line), 0);
	var->len = ft_strlen (line);
	while (line[var->i])
	{
		if (line[var->i] == '$')
			code_status(var, line, envp);
		else
		{
			var->data[var->x] = line[var->i];
			var->x++;
			var->i++;
		}
	}
	var->data[var->x] = '\0';
	return (var->data);
}
