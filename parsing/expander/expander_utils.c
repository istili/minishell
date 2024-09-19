/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 01:18:26 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/14 14:35:25 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_realloc(void *ptr, int new_size, int len)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (ptr == NULL)
		return (ft_malloc_gab(new_size, 0));
	new_ptr = ft_malloc_gab(new_size, 0);
	ft_memcpy(new_ptr, ptr, len);
	return (new_ptr);
}

void	to_initial(t_values *var, int start, int end)
{
	var->i = -1;
	var->e_status = ft_itoa(exit_status(0, 0));
	var->len = end - start + 1;
	var->value = ft_malloc_gab(var->len + 1, 0);
}

void	store(int start, int end, t_values *var, char *line)
{
	while (start <= end)
		var->value[++var->i] = line[start++];
}

char	*ft_replace(char *line, int start, int end, t_link *envp)
{
	t_values	*var;
	char		*data;

	data = NULL;
	var = ft_malloc_gab(sizeof(t_values), 0);
	to_initial(var, start, end);
	if (line[start] == '?')
	{
		data = ft_malloc_gab(var->len + 4, 0);
		while (var->e_status[++var->i])
			data[var->i] = var->e_status[var->i];
		start++;
		while (start < end)
			data[var->i++] = line[start++];
		data[var->i] = '\0';
	}
	else
	{
		store(start, end, var, line);
		var->value[var->i] = '\0';
		data = find_val(envp, var->value);
	}
	if (!data)
		return (ft_strdup(""));
	return (data);
}
