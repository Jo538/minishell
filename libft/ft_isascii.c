/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:02:05 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/24 16:12:58 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks whether c is a 7-bit unsigned char value 
 * that  fits  into the ASCII character set.
 * 
 * @param n The character to check
 * @return int Returns 1 if n is in the ASCII table, 0 if 
 * it's not in the ASCII table
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	(void)argc;
	int	n;

	n = atoi(argv[1]);
	printf("isascii: %d\n", isascii(n));
	printf("ft_isascii: %d\n", ft_isascii(n));
}*/
