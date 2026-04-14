/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:18:33 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/18 14:19:36 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks  for an alphabetic character
 * 
 * @param c The character to check
 * @return int Returns 1 if c is in the alphabet, 0 if it's not in the alphabet
 */
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	(void)argc;

	printf("isalpha: %d\n", isalpha(*argv[1]));
	printf("ft_isalpha: %d\n", ft_isalpha(*argv[1]));
}*/
