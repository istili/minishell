/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:19:20 by hfiqar            #+#    #+#             */
/*   Updated: 2024/09/14 17:07:41 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*check_for_file(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str) - 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (len >= 0 && (str[len] == ' ' || str[len] == '\t'))
		len --;
	str[len + 1] = '\0';
	return (str + i);
}
