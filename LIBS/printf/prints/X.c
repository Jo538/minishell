/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   X.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bribot <bribot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:53:01 by bribot            #+#    #+#             */
/*   Updated: 2026/01/27 17:01:41 by bribot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int	inull(void)
{
	write (1, "0", 1);
	return (1);
}

static int	countlen(unsigned int i)
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

int	upperx(unsigned int i)
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
	base_hex = "0123456789ABCDEF";
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
