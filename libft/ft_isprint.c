/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:01:59 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/18 14:24:29 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks for any printable character including space.
 * 
 * @param c The character to check
 * @return int Returns 1 if c is a printable character, 0 if 
 * it's not a printable character
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int	main(void)
{
	char	n;

	n = '\n';

	printf("ft_isprint: %d\n", ft_isprint(n));
	printf("isprint: %d\n", isprint(n));
}*/