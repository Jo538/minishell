/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:18:33 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/18 14:18:22 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief checks for an alphanumeric character
 * 
 * @param c The character to check
 * @return int Returns 1 if c is alphanumeric, 0 if it's not alphanumeric
 */
int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	(void)argc;

	printf("isalnum: %d\n", isalnum(*argv[1]));
	printf("ft_isalnum: %d\n", ft_isalnum(*argv[1]));
}*/
