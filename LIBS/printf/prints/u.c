/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:39:21 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_put_unsigned_nbr(unsigned int nb)
{
	unsigned int	tmp;

	if (nb > 9)
		ft_put_unsigned_nbr(nb / 10);
	tmp = (nb % 10) + 48;
	write(1, &tmp, 1);
}

static int	ft_count_len(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

int	u(unsigned int i)
{
	int	j;

	ft_put_unsigned_nbr(i);
	j = ft_count_len(i);
	return (j);
}
