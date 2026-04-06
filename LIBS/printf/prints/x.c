/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:58:56 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	inull(void)
{
	write (1, "0", 1);
	return (1);
}

static int	countlen(unsigned long int i)
{
	int	j;

	j = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		i = i / 16;
		j++;
	}
	return (j);
}

int	x(unsigned long int i)
{
	char	*base_hex;
	char	*dest;
	int		j;
	int		k;

	j = 0;
	k = countlen(i);
	if (i == 0)
		return (inull());
	dest = malloc (countlen(i) + 1);
	if (!dest)
		return (0);
	dest[countlen(i)] = 0;
	base_hex = "0123456789abcdef";
	while (i != 0)
	{
		dest[j] = base_hex[i % 16];
		i = i / 16;
		j++;
	}
	while (j > 0)
		write(1, &dest[--j], 1);
	free (dest);
	return (k);
}

// int	main(void)
// {
// 	int	j;

// 	j = x(INT_MAX);
// 	printf("\n%d \n%x", j, INT_MAX);
// 	return (0);
// }