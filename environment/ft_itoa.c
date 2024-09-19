/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 01:48:58 by istili            #+#    #+#             */
/*   Updated: 2024/07/31 12:17:00 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_digits(long n)
{
	int	nbr_digits;

	nbr_digits = 0;
	if (n <= 0)
	{
		nbr_digits++;
		n = -n;
	}
	while (n > 0)
	{
		nbr_digits++;
		n /= 10;
	}
	return (nbr_digits);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*ret;

	nb = (long)n;
	i = count_digits(nb);
	ret = ft_malloc_gab(i + 1, 0);
	if (nb < 0)
	{
		ret[0] = '-';
		nb = -nb;
	}
	ret[i] = '\0';
	i--;
	if (nb == 0)
		ret[0] = '0';
	while (nb > 0)
	{
		ret[i] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	return (ret);
}
