/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:16:57 by jchartie          #+#    #+#             */
/*   Updated: 2025/11/18 14:54:52 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The tolower() function returns the ASCII value of a lowercase 
 * version of the character. If the character is not an uppercase character 
 * then its value is returned without being changed.
 * 
 * @param c The ASCII value of a character or an actual character.
 * @return int An int value representing the ASCII value of the lowercase 
 * version of a character.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}
/*
int	main(void)
{
	char	c;

	c = 'Z';
	printf("tolower: %c\n", tolower(c));

	c = 'Z';
	printf("ft_tolower: %c", ft_tolower(c));
}*/