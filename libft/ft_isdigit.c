/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:05:35 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/19 21:34:02 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief checks for a digit (0 through 9).
 * 
 * @param c The character to check
 * @return int Returns 1 if c is a digit, 0 if 
 * it's not a digit
 */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	(void)argc;

	printf("isdigit: %d\n", isdigit(*argv[1]));
	printf("ft_isdigit: %d\n", ft_isdigit(*argv[1]));
}*/
